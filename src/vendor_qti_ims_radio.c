#include <ofono/log.h>
#include <gbinder.h>
#include <glib.h>
#include <gutil_idlepool.h>

#include "vendor_qti_ims_radio.h"

#define DEFAULT_INTERFACE IMS_RADIO_INTERFACE_1_2

static const GBinderClientIfaceInfo ims_radio_iface_info[] = {
    {IMS_RADIO_1_2, IMS_RADIO_1_2_REQ_LAST },
    {IMS_RADIO_1_1, IMS_RADIO_1_1_REQ_LAST },
    {IMS_RADIO_1_0, IMS_RADIO_1_0_REQ_LAST }
};
G_STATIC_ASSERT(G_N_ELEMENTS(ims_radio_iface_info) == IMS_RADIO_INTERFACE_COUNT);

static const char* const ims_radio_indication_ifaces[] = {
    IMS_RADIO_INDICATION_1_2,
    IMS_RADIO_INDICATION_1_1,
    IMS_RADIO_INDICATION_1_0,
    NULL
};
G_STATIC_ASSERT(G_N_ELEMENTS(ims_radio_indication_ifaces) == IMS_RADIO_INTERFACE_COUNT + 1);

static const char* const ims_radio_response_ifaces[] = {
    IMS_RADIO_RESPONSE_1_2,
    IMS_RADIO_RESPONSE_1_1,
    IMS_RADIO_RESPONSE_1_0,
    NULL
};
G_STATIC_ASSERT(G_N_ELEMENTS(ims_radio_response_ifaces) == IMS_RADIO_INTERFACE_COUNT + 1);

typedef struct ims_radio_interface_desc {
    RADIO_INTERFACE version;
    const char* radio_iface;
    const char* const* ind_ifaces;
    const char* const* resp_ifaces;
} ImsRadioInterfaceDesc;

#define IMS_RADIO_INTERFACE_INDEX(x) (IMS_RADIO_INTERFACE_COUNT - x - 1)

#define IMS_RADIO_INTERFACE_DESC(v) \
        IMS_RADIO_INTERFACE_##v, IMS_RADIO_##v, \
        ims_radio_indication_ifaces + IMS_RADIO_INTERFACE_INDEX(IMS_RADIO_INTERFACE_##v), \
        ims_radio_response_ifaces + IMS_RADIO_INTERFACE_INDEX(IMS_RADIO_INTERFACE_##v)

static const RadioInterfaceDesc ims_radio_interfaces[] = {
   { IMS_RADIO_INTERFACE_DESC(1_2) },
   { IMS_RADIO_INTERFACE_DESC(1_1) },
   { IMS_RADIO_INTERFACE_DESC(1_0) }
};
G_STATIC_ASSERT(G_N_ELEMENTS(ims_radio_interfaces) == IMS_RADIO_INTERFACE_COUNT);


typedef GObjectClass VendorQtiImsRadioClass;
struct qti_ims_radio {
    GObject parent;
    char* name;
    GBinderClient* client;
    GBinderRemoteObject* remote;
    GBinderLocalObject* response;
    GBinderLocalObject* indication;
    GUtilIdlePool* idle;
    GHashTable* table;
};

G_DEFINE_TYPE(VendorQtiImsRadio, qti_ims_radio, G_TYPE_OBJECT)

#define THIS_TYPE qti_ims_radio_get_type()
#define THIS(obj) G_TYPE_CHECK_INSTANCE_CAST(obj, THIS_TYPE, VendorQtiImsRadio)
#define IS_THIS(obj) G_TYPE_CHECK_INSTANCE_TYPE(obj, THIS_TYPE)
#define PARENT_CLASS qti_ims_radio_parent_class

/*==========================================================================*
 * Internals
 *==========================================================================*/
static
void
qti_ims_radio_finalize(
    GObject* object)
{
    VendorQtiImsRadio* self = THIS(object);

    g_hash_table_unref(self->table);
    gbinder_client_unref(self->client);
    gutil_idle_pool_destroy(self->idle);
    G_OBJECT_CLASS(PARENT_CLASS)->finalize(object);
}

static void destroy_value(gpointer hash_data) {
    printf("destroy value:%s\n",hash_data);
    //因为我这里的值是数组形式不是指针所以不用释放内存。我就直接清空吧
/*    free(hash_data);
    hash_data = NULL;*/
    //memset(hash_data,0,sizeof(hash_data));
}
static
void
qti_ims_radio_init(
    VendorQtiImsRadio* self)
{
    self->idle = gutil_idle_pool_new();
    self->table = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, destroy_value);
}

static
void
qti_ims_radio_class_init(
    VendorQtiImsRadioClass* klass)
{
    G_OBJECT_CLASS(klass)->finalize = qti_ims_radio_finalize;
    // g_signal_new
}

/**
vendor_qti_ims_radio_registration_info
vendor_qti_ims_radio_get_reg_state_response
vendor_qti_ims_radio_send_ims_sms_response
vendor_qti_ims_radio_sip_result_response

vendor_qti_ims_radio_response
vendor_qti_ims_radio_indication
vendor_qti_ims_radio_handle_supp_service_notification
vendor_qti_ims_radio_handle_call_state_changed
vendor_qti_ims_radio_handle_sms_status_report
vendor_qti_ims_radio_handle_incoming_ims_sms
*/

/*==========================================================================*
 * API
 *==========================================================================*/
VendorQtiImsRadio* vendor_qti_ims_radio_new(const char* dev, const char* name)
{
    return vendor_qti_ims_radio_new_with_version(dev, name, DEFAULT_INTERFACE);
}
VendorQtiImsRadio* radio_instance_new_with_version(
    const char* dev,
    const char* name,
    RADIO_INTERFACE version) /* Since 1.2.1 */
{
    VendorQtiImsRadio* self = NULL;
    GBinderServiceManager* sm = gbinder_servicemanager_new(dev);
    if (sm) {
        guint i;
        for (i = 0; i < G_N_ELEMENTS(ims_radio_interfaces) && !self; i++) {
            const ImsRadioInterfaceDesc* desc = ims_radio_interfaces + i;

            if (desc->version <= max_version) {
                char* fqname = g_strconcat(desc->radio_iface, "/", name, NULL);
                GBinderRemoteObject* obj = gbinder_servicemanager_get_service_sync(sm, fqname, NULL);

                if (obj) {
                    GINFO("Connected to %s", fqname);
                    self = vendor_qti_ims_radio_create(sm, obj, dev, name, desc);
                }
                g_free(fqname);
            }
        }
        gbinder_servicemanager_unref(sm);
    }
    return self;
}

VendorQtiImsRadio* vendor_qti_ims_radio_create(
    GBinderServiceManager* sm,
    GBinderRemoteObject* remote,
    const char* dev,
    const char* name,
    const ImsRadioInterfaceDesc* desc)
{
    VendorQtiImsRadio* self = g_object_new(THIS_TYPE, NULL);
    int status;

}
