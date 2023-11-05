
#include "plugin.h"
#include "binder_ext_ims.h"
#include "binder_ext_plugin_impl.h"
#include "binder_ext_slot_impl.h"

/*==========================================================================*
 * QTI plugin
 *==========================================================================*/

typedef BinderExtPluginClass VendorQtiExtClass;
typedef struct qti_plugin {
    BinderExtPlugin parent;
    void* b_40;
    int num;

} VendorQtiExt;

G_DEFINE_TYPE(VendorQtiExt, qti_plugin, BINDER_EXT_TYPE_PLUGIN)

#define QTI_TYPE_PLUGIN qti_plugin_get_type()
#define QTI_PLUGIN(obj) G_TYPE_CHECK_INSTANCE_CAST(obj, \
        QTI_TYPE_PLUGIN, VendorQtiExt)

static const char qti_plugin_name[] = "qti";

static
BinderExtSlot*
qti_plugin_new_slot(
    BinderExtPlugin* plugin,
    RadioInstance* radio,
    GHashTable* params)
{
    VendorQtiSlot* slot = g_object_new(QTI_TYPE_SLOT, NULL);
    VendorQtiExt* self =  QTI_PLUGIN(plugin);
    char* ims_radio_num = g_strdup_printf("imsradio%d", self->num);
    //
    VendorQtiImsRadio* ims_radio = vendor_qti_ims_radio_new(self->b_40,ims_radio_num,2);
    slot->ims_radio = ims_radio;
    if(ims_radio != NULL){
        VendorQtiImsStateObject* ims_state = vendor_qti_ims_state_new(ims_radio);
        slot->ims_state = ims_state;
        slot->ims = vendor_qti_ims_new(ims_radio,ims_state);
        slot->ims_call = vendor_qti_ims_call_new(slot->ims_radio,slot->ims_state);
        slot->ims_sms = vendor_qti_ims_sms_new(slot->ims_radio,slot->ims_state);
    }
    g_free(ims_radio_num);
    return slot;
}

static
void
qti_plugin_init(
    VendorQtiExt* self)
{
}

static
void
qti_plugin_class_init(
    VendorQtiExtClass* klass)
{
    klass->plugin_name = qti_plugin_name;
    klass->new_slot = qti_plugin_new_slot;
}



// sub_B940
static int vendor_qti_plugin_init(void){

  BinderExtPlugin* plugin = g_object_new(QTI_TYPE_PLUGIN, NULL);

  binder_ext_plugin_register(plugin);
  binder_ext_plugin_unref(plugin);
  return 0;
}
// sub_B8F8
static void vendor_qti_plugin_exit(void){

}

OFONO_PLUGIN_DEFINE(vendor_qti, "Vendor QTI plugin", "1.28",
                    OFONO_PLUGIN_PRIORITY_DEFAULT, vendor_qti_plugin_init, vendor_qti_plugin_exit)

/**
 * VendorQtiExt
 * VendorQtiIms
 * VendorQtiImsCall
 * VendorQtiImsConfObject
 * VendorQtiImsRadio
 * VendorQtiImsSms
 * VendorQtiImsStateObject
 * VendorQtiSlot
 * 
 * 
 * */