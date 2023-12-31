#ifndef VENDOR_QTI_IMS_RADIO_H
#define VENDOR_QTI_IMS_RADIO_H

#include <binder_ext_slot.h>

#include <radio_types.h>
#include "vendor_qti_types.h"

#define IMS_RADIO_IFACE_PREFIX     "vendor.qti.hardware.radio.ims@"
#define IMS_RADIO_IFACE            "IImsRadio"
#define IMS_RADIO_RESPONSE_IFACE   "IImsRadioResponse"
#define IMS_RADIO_INDICATION_IFACE "IImsRadioIndication"
#define IMS_RADIO_IFACE_1_0(x)     IMS_RADIO_IFACE_PREFIX "1.0::" x
#define IMS_RADIO_IFACE_1_1(x)     IMS_RADIO_IFACE_PREFIX "1.1::" x
#define IMS_RADIO_IFACE_1_2(x)     IMS_RADIO_IFACE_PREFIX "1.2::" x
#define IMS_RADIO_1_0              IMS_RADIO_IFACE_1_0(IMS_RADIO_IFACE)
#define IMS_RADIO_1_1              IMS_RADIO_IFACE_1_1(IMS_RADIO_IFACE)
#define IMS_RADIO_1_2              IMS_RADIO_IFACE_1_2(IMS_RADIO_IFACE)
#define IMS_RADIO_RESPONSE_1_0     IMS_RADIO_IFACE_1_0(IMS_RADIO_RESPONSE_IFACE)
#define IMS_RADIO_RESPONSE_1_1     IMS_RADIO_IFACE_1_1(IMS_RADIO_RESPONSE_IFACE)
#define IMS_RADIO_RESPONSE_1_2     IMS_RADIO_IFACE_1_2(IMS_RADIO_RESPONSE_IFACE)
#define IMS_RADIO_INDICATION_1_0   IMS_RADIO_IFACE_1_0(IMS_RADIO_INDICATION_IFACE)
#define IMS_RADIO_INDICATION_1_1   IMS_RADIO_IFACE_1_1(IMS_RADIO_INDICATION_IFACE)
#define IMS_RADIO_INDICATION_1_2   IMS_RADIO_IFACE_1_2(IMS_RADIO_INDICATION_IFACE)


VendorQtiImsRadio* vendor_qti_ims_radio_new(const char* dev, const char* name);

#endif
