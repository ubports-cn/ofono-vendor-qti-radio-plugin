
#include "vendor_qti_util.h"


// vendor_qti_util_markup_parse

const char*
vendor_qti_util_radio_req_name(
    IMS_RADIO_REQ req)
{
    switch (req) {
#define IMS_RADIO_REQ_(req,resp,Name,NAME) \
    case RADIO_REQ_##NAME: return #Name;
    IMS_RADIO_CALL_1_0(IMS_RADIO_REQ_)
    IMS_RADIO_CALL_1_2(IMS_RADIO_REQ_)
#undef IMS_RADIO_REQ_
    case IMS_RADIO_REQ_SET_CALLBACK:   return "setCallback";
    case IMS_RADIO_REQ_SET_COLR:     return "setColr";
    case IMS_RADIO_REQ_HANGUP_1_1:  return "hangup_1_1";
    case IMS_RADIO_REQ_HANGUP_1_2:        return "hangup_1_2";
    case IMS_RADIO_REQ_ACKNOWLEDGE_SMS:   return "acknowledgeSms";
    case IMS_RADIO_REQ_ACKNOWLEDGE_SMS_REPORT: return "acknowledgeSmsReport";
    case IMS_RADIO_REQ_ANY:
        break;
    }
    return NULL;
}

const char*
vendor_qti_util_radio_resp_name(
    IMS_RADIO_RESP resp)
{
    switch (resp) {
#define IMS_RADIO_RESP_(req,resp,Name,NAME) \
    case RADIO_RESP_##NAME: return #Name "Response";
    IMS_RADIO_CALL_1_0(IMS_RADIO_RESP_)
    IMS_RADIO_CALL_1_2(IMS_RADIO_RESP_)
#undef IMS_RADIO_RESP_
    case IMS_RADIO_RESP_ANY:
        break;
    }
    return NULL;
}

const char*
vendor_qti_util_radio_ind_name(
    IMS_RADIO_IND ind)
{
    switch (ind) {
#define IMS_RADIO_IND_(code,Name,NAME) \
    case IMS_RADIO_IND_##NAME: return #Name;
    IMS_RADIO_EVENT_1_0(IMS_RADIO_IND_)
    IMS_RADIO_EVENT_1_1(IMS_RADIO_IND_)
    IMS_RADIO_EVENT_1_2(IMS_RADIO_IND_)
#undef IMS_RADIO_IND_
    case IMS_RADIO_IND_ANY:
        break;
    }
    return NULL;
}