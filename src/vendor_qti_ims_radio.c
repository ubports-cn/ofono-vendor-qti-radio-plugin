#include <ofono/log.h>
#include <gbinder.h>

#include "vendor_qti_ims_radio.h"

typedef struct radio_interface_desc {
    RADIO_INTERFACE version;
    const char* radio_iface;
    const char* const* ind_ifaces;
    const char* const* resp_ifaces;
} RadioInterfaceDesc;

typedef GObjectClass VendorQtiImsRadioClass;
struct qti_ims_radio {
    GObject parent;
    int num;

};

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
#define DEFAULT_INTERFACE 2

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
/**
        for (i = 0; i < G_N_ELEMENTS(radio_interfaces) && !self; i++) {
            const RadioInterfaceDesc* desc = radio_interfaces + i;

            if (desc->version <= max_version) {
                char* fqname = g_strconcat(desc->radio_iface, "/", name, NULL);
                GBinderRemoteObject* obj = gbinder_servicemanager_get_service_sync(sm, fqname, NULL);

                if (obj) {
                    GINFO("Connected to %s", fqname);
                    self = vendor_qti_ims_radio_create(sm, obj, dev, slot,
                        key, modem, slot_index, desc);
                }
                g_free(fqname);
            }
        }
*/
        gbinder_servicemanager_unref(sm);
    }
    return self;
}
/**
VendorQtiImsRadio* vendor_qti_ims_radio_create(
    GBinderServiceManager* sm,
    GBinderRemoteObject* remote,
    const char* dev,
    const char* slot,
    const char* key,
    const char* modem,
    int slot_index,
    const RadioInterfaceDesc* desc)
{
    int status;

}
*/