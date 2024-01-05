#include <ofono/log.h>
#include "vendor_qti_types.h"

typedef BinderExtCallClass VendorQtiImsCallClass;
struct qti_ims_call {
    BinderExtCall parent;
    void * v_1;
    void * v_2;
    void * v_3;
    void * v_4;
    void * v_5;
    void * v_6;
};

G_DEFINE_TYPE(VendorQtiImsCall, qti_ims_call, BINDER_EXT_TYPE_CALL)

#define QTI_IMS_CALL_TYPE_SLOT qti_ims_call_get_type()
#define QTI_IMS_CALL_SLOT(obj) G_TYPE_CHECK_INSTANCE_CAST(obj, QTI_IMS_CALL_TYPE_SLOT, VendorQtiImsCall)
#define QTI_IMS_CALL_IS_SLOT(obj) G_TYPE_CHECK_INSTANCE_TYPE(obj, QTI_IMS_CALL_TYPE_SLOT)



vendor_qti_ims_call_conference_info_start_element
vendor_qti_ims_call_reg_state_update
vendor_qti_ims_call_hangup
vendor_qti_ims_call_send_dtmf
vendor_qti_ims_call_conference
vendor_qti_ims_call_conference_request_complete
vendor_qti_ims_call_swap
vendor_qti_ims_call_result_request_continue
vendor_qti_ims_call_result_request_continue_resume
vendor_qti_ims_call_result_request_continue_answer
vendor_qti_ims_call_answer
vendor_qti_ims_call_dial
vendor_qti_ims_call_handle_conference_info
vendor_qti_ims_call_handle_conf_user_deleted
vendor_qti_ims_call_handle_conf_user_info_changed
vendor_qti_ims_call_handle_state_change
