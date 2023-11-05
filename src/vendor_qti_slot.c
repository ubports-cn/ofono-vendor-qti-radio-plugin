
#include "plugin.h"
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

#define QTI_TYPE_SLOT qti_slot_get_type()
#define QTI_SLOT(obj) G_TYPE_CHECK_INSTANCE_CAST(obj, QTI_TYPE_SLOT, VendorQtiSlot)
#define QTI_IS_SLOT(obj) G_TYPE_CHECK_INSTANCE_TYPE(obj, QTI_TYPE_SLOT)

static
gpointer
qti_slot_get_interface(
    BinderExtSlot* slot,
    GType iface)
{
    return BINDER_EXT_SLOT_CLASS(qti_slot_parent_class)->
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
    BINDER_EXT_SLOT_CLASS(qti_slot_parent_class)->shutdown(slot);
}
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