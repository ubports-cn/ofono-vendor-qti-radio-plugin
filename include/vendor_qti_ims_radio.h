#ifndef VENDOR_QTI_IMS_RADIO_H
#define VENDOR_QTI_IMS_RADIO_H

#include <binder_ext_slot.h>

#include <radio_types.h>
#include "vendor_qti_types.h"

/* c(req,resp,callName,CALL_NAME) */
#define IMS_RADIO_CALL_1_0(c) \
    c(2,1,dial,DIAL) \
    c(3,31,addParticipant,ADD_PARTICIPANT) \
    c(4,11,getRegistrationState,GET_REGISTRATION_STATE) \
    c(5,2,answer,ANSWER) \
    c(6,3,hangup,HANGUP) \
    c(7,4,requestRegistrationChange,REQUEST_REGISTRATION_CHANGE) \
    c(8,5,queryServiceStatus,QUERY_SERVICE_STATUS) \
    c(9,6,setServiceStatus,SET_SERVICE_STATUS) \
    c(10,7,hold,HOLD) \
    c(11,8,resume,RESUME) \
    c(12,9,setConfig,SET_CONFIG) \
    c(13,10,getConfig,GET_CONFIG) \
    c(14,13,conference,CONFERENCE) \
    c(15,14,getClip,GET_CLIP) \
    c(16,15,getClir,GET_CLIR) \
    c(17,16,setClir,SET_CLIR) \
    c(18,17,getColr,GET_COLR) \
    c(20,18,exitEmergencyCallbackMode,EXIT_EMERGENCY_CALLBACK_MODE) \
    c(21,19,sendDtmf,SEND_DTMF) \
    c(22,20,startDtmf,START_DTMF) \
    c(23,21,stopDtmf,STOP_DTMF) \
    c(24,22,setUiTtyMode,SET_UI_TTY_MODE) \
    c(25,23,modifyCallInitiate,MODIFY_CALL_INITIATE) \
    c(26,24,modifyCallConfirm,MODIFY_CALL_CONFIRM) \
    c(27,25,queryCallForwardStatus,QUERY_CALL_FORWARD_STATUS) \
    c(29,26,getCallWaiting,GET_CALL_WAITING) \
    c(31,28,setSuppServiceNotification,SET_SUPP_SERVICE_NOTIFICATION) \
    c(32,27,explicitCallTransfer,EXPLICIT_CALL_TRANSFER) \
    c(33,12,suppServiceStatus,SUPP_SERVICE_STATUS) \
    c(34,29,getRtpStatistics,GET_RTP_STATISTICS) \
    c(35,30,getRtpErrorStatistics,GET_RTP_ERROR_STATISTICS) \
    c(36,32,deflectCall,DEFLECT_CALL) \
    c(37,33,sendGeolocationInfo,SEND_GEOLOCATION_INFO) \
    c(38,34,getImsSubConfig,GET_IMS_SUB_CONFIG) \
    c(39,35,sendRttMessage,SEND_RTT_MESSAGE) \
    c(40,36,cancelModifyCall,CANCEL_MODIFY_CALL)

#define IMS_RADIO_CALL_1_2(c) /* Since 1.2.0 */ \
    c(43,37,sendImsSms,SEND_IMS_SMS)

typedef enum ims_radio_req {
    IMS_RADIO_REQ_ANY = 0,
    IMS_RADIO_REQ_NONE = 0,
#define IMS_RADIO_REQ_(req,resp,Name,NAME) IMS_RADIO_REQ_##NAME = req,

    /* vendor.qti.hardware.radio.ims@1.0::IImsRadio */
    IMS_RADIO_REQ_SET_CALLBACK = 1, /* setCallback */
    IMS_RADIO_CALL_1_0(IMS_RADIO_REQ_)
    IMS_RADIO_REQ_SET_COLR = 19,
    IMS_RADIO_1_0_REQ_LAST = IMS_RADIO_REQ_CANCEL_MODIFY_CALL,

    /* vendor.qti.hardware.radio.ims@1.1::IImsRadio */
    IMS_RADIO_REQ_HANGUP_1_1 = 41,
    IMS_RADIO_1_1_REQ_LAST = IMS_RADIO_REQ_HANGUP_1_1,

    /* vendor.qti.hardware.radio.ims@1.2::IImsRadio */
    IMS_RADIO_REQ_HANGUP_1_2 = 42,
    IMS_RADIO_CALL_1_2(IMS_RADIO_REQ_)
    IMS_RADIO_REQ_ACKNOWLEDGE_SMS = 44,
    IMS_RADIO_REQ_ACKNOWLEDGE_SMS_REPORT = 45,
    IMS_RADIO_REQ_UNKOWN_1 = 46,
    IMS_RADIO_REQ_UNKOWN_2 = 47,
    IMS_RADIO_1_2_REQ_LAST = IMS_RADIO_REQ_UNKOWN_2,
#undef IMS_RADIO_REQ_
} IMS_RADIO_REQ;
G_STATIC_ASSERT(sizeof(IMS_RADIO_REQ) == 4);

typedef enum ims_radio_resp {
    IMS_RADIO_RESP_ANY = 0,
    IMS_RADIO_RESP_NONE = 0,
#define IMS_RADIO_RESP_(req,resp,Name,NAME) IMS_RADIO_RESP_##NAME = resp,

    /* vendor.qti.hardware.radio.ims@1.1::IImsRadioResponse */
    IMS_RADIO_CALL_1_0(IMS_RADIO_RESP_)
    IMS_RADIO_1_0_RESP_LAST = IMS_RADIO_RESP_CANCEL_MODIFY_CALL,

    /* vendor.qti.hardware.radio.ims@1.1::IImsRadioResponse */
    IMS_RADIO_1_1_RESP_LAST = IMS_RADIO_1_0_RESP_LAST,

    /* vendor.qti.hardware.radio.ims@1.1::IImsRadioResponse */
    IMS_RADIO_CALL_1_2(IMS_RADIO_RESP_)
    IMS_RADIO_1_2_RESP_LAST = IMS_RADIO_RESP_SEND_IMS_SMS,

#undef IMS_RADIO_RESP_
} IMS_RADIO_RESP;
G_STATIC_ASSERT(sizeof(IMS_RADIO_RESP) == 4);


typedef enum ims_radio_interface {
    IMS_RADIO_INTERFACE_NONE = -1, /* Since 1.4.3 */
    IMS_RADIO_INTERFACE_1_0,
    IMS_RADIO_INTERFACE_1_1,
    IMS_RADIO_INTERFACE_1_2,
    IMS_RADIO_INTERFACE_COUNT
} IMS_RADIO_INTERFACE; /* Since 1.2.0 */


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
