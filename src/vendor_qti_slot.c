
#include "vendor_qti_slot.h"
#include "binder_ext_ims.h"
#include "binder_ext_slot_impl.h"


/*==========================================================================*
 * QTI slot
 *==========================================================================*/

typedef BinderExtSlotClass VendorQtiSlotClass;
typedef struct qti_slot {
    BinderExtSlot parent;
    int* shutdown;
    VendorQtiIms* ims;// 4
    VendorQtiImsSms* ims_sms;// 5
    VendorQtiImsCall* ims_call;// 6
    VendorQtiImsRadio* ims_radio;// 7
    VendorQtiImsStateObject* ims_state; // 8
} VendorQtiSlot;

G_DEFINE_TYPE(VendorQtiSlot, qti_slot, BINDER_EXT_TYPE_SLOT)

#define THIS_TYPE qti_slot_get_type()
#define THIS(obj) G_TYPE_CHECK_INSTANCE_CAST(obj, THIS_TYPE, VendorQtiSlot)
#define IS_THIS(obj) G_TYPE_CHECK_INSTANCE_TYPE(obj, THIS_TYPE)
#define PARENT_CLASS qti_slot_parent_class


/*==========================================================================*
 * BinderExtSlotClass
 *==========================================================================*/
 
static
gpointer
qti_slot_get_interface(
    BinderExtSlot* slot,
    GType iface)
{
    return BINDER_EXT_SLOT_CLASS(PARENT_CLASS)->
        get_interface(slot, iface);
}

static
void
qti_slot_shutdown(
    BinderExtSlot* slot)
{
    VendorQtiSlot* self = QTI_SLOT(slot);

    if (self->shutdown) {
        (*self->shutdown)++;
    }
    BINDER_EXT_SLOT_CLASS(PARENT_CLASS)->shutdown(slot);
}

/*==========================================================================*
 * API
 *==========================================================================*/
 BinderExtSlot* vendor_qti_slot_new(RadioInstance* radio, GHashTable* params)
{
    VendorQtiSlot* slot = g_object_new(QTI_TYPE_SLOT, NULL);

    char* ims_radio_num = g_strdup_printf("imsradio%d", radio->slot_index);
    //
    VendorQtiImsRadio* ims_radio = vendor_qti_ims_radio_new(radio->enabled,ims_radio_num,2);
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

/*==========================================================================*
 * Internals
 *==========================================================================*/
 
static
void
qti_slot_init(
    VendorQtiSlot* self)
{
}

static
void
qti_slot_class_init(
    VendorQtiSlotClass* klass)
{
    klass->get_interface = qti_slot_get_interface;
    klass->shutdown = qti_slot_shutdown;
}



