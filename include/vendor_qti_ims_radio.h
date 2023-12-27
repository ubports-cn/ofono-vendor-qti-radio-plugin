#ifndef VENDOR_QTI_SLOT_H
#define VENDOR_QTI_SLOT_H

#include <binder_ext_slot.h>

#include <radio_types.h>

VendorQtiImsRadio* vendor_qti_ims_radio_new(RadioInstance* radio, GHashTable* params);

#endif
