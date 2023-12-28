
#include "vendor_qti_ims_radio.h"

typedef VendorQtiImsRadioClass VendorQtiExtClass;
typedef struct qti_ims_radio {
    BinderExtPlugin parent;
    int num;

} VendorQtiImsRadio;


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


/*==========================================================================*
 * API
 *==========================================================================*/
 vendor_qti_ims_radio_new(){
 }

 vendor_qti_ims_radio_create()