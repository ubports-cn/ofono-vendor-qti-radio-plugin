#ifndef VENDOR_QTI_SLOT_H
#define VENDOR_QTI_SLOT_H

#include <binder_ext_slot.h>

#include <radio_types.h>

BinderExtSlot* vendor_qti_slot_new(RadioInstance* radio, GHashTable* params);

#endif
