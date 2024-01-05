
#include <ofono/log.h>

#include "radio_instance.h"

#include "binder_ext_ims.h"
#include "binder_ext_sms.h"
#include "binder_ext_call.h"

#include "binder_ext_slot_impl.h"

#include "vendor_qti_types.h"

#include "vendor_qti_slot.h"
#include "vendor_qti_ims_radio.h"
#include "vendor_qti_ims_state.h"


/*==========================================================================*
 * QTI slot
 *==========================================================================*/

typedef BinderExtSlotClass VendorQtiSlotClass;
struct qti_slot {
    BinderExtSlot parent;
    BinderExtIms* ims;// 4
    BinderExtSms* ims_sms;// 5
    BinderExtCall* ims_call;// 6
    VendorQtiImsRadio* ims_radio;// 7
    VendorQtiImsStateObject* ims_state; // 8
};

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
    VendorQtiSlot *self = THIS(slot);
    if (iface == BINDER_EXT_TYPE_IMS) {
        return self->ims;
    }
    if (iface == BINDER_EXT_TYPE_SMS) {
        return self->ims_sms;
    }
    if (iface == BINDER_EXT_TYPE_CALL) {
        return self->ims_call;
    }
    return BINDER_EXT_SLOT_CLASS(PARENT_CLASS)->
        get_interface(slot, iface);
}

static
void
qti_slot_shutdown(
    BinderExtSlot* slot)
{
    VendorQtiSlot* self = THIS(slot);

    BINDER_EXT_SLOT_CLASS(PARENT_CLASS)->shutdown(slot);
}

/*==========================================================================*
 * API
 *==========================================================================*/
 BinderExtSlot* vendor_qti_slot_new(RadioInstance* radio, GHashTable* params)
{
    VendorQtiSlot* self = g_object_new(THIS_TYPE, NULL);
    BinderExtSlot* slot = &self->parent;
    char* ims_radio_name = g_strdup_printf("imsradio%d", radio->slot_index);
    //
    VendorQtiImsRadio* ims_radio = vendor_qti_ims_radio_new(radio->dev, ims_radio_name);
    self->ims_radio = ims_radio;
    /*
    if(ims_radio != NULL){
        VendorQtiImsStateObject* ims_state = vendor_qti_ims_state_new(ims_radio);
        self->ims_state = ims_state;
        self->ims = vendor_qti_ims_new(ims_radio,ims_state);
        self->ims_call = vendor_qti_ims_call_new(self->ims_radio,self->ims_state);
        self->ims_sms = vendor_qti_ims_sms_new(self->ims_radio,self->ims_state);
    }
    */
    g_free(ims_radio_name);
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



