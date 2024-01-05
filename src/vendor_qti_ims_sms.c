#include <ofono/log.h>
#include "binder_ext_sms_impl.h"

#include "vendor_qti_types.h"


typedef GObjectClass VendorQtiImsSmsClass;
struct qti_ims_sms {
    GObject parent;
    int cancelled;
    VendorQtiImsRadio* ims_radio;
    VendorQtiImsStateObject* ims_state;
};

static void qti_ims_sms_iface_init(BinderExtSmsInterface* iface);
G_DEFINE_TYPE_WITH_CODE(VendorQtiImsSms, qti_ims_sms, G_TYPE_OBJECT,
G_IMPLEMENT_INTERFACE(BINDER_EXT_TYPE_SMS, qti_ims_sms_iface_init))

#define QTI_TYPE_SMS qti_ims_sms_get_type()
#define QTI_IMS_SMS(obj) G_TYPE_CHECK_INSTANCE_CAST(obj, QTI_TYPE_SMS, VendorQtiImsSms)

static
void
qti_ims_sms_init(
    VendorQtiImsSms* self)
{
}

static
void
qti_ims_sms_class_init(
    VendorQtiImsSmsClass* klass)
{
    sms_incoming_signal = g_signal_new("qti-ims-sms-incoming", 
                                    G_TYPE_FROM_CLASS (klass), 
                                    1LL, 0LL, 0LL, 0LL, 0LL, 4LL, 2, 68LL);
    sms_status_report_signal = g_signal_new("qti-ims-sms-status-report", 
                                    G_TYPE_FROM_CLASS (klass), 
                                    1LL, 0LL, 0LL, 0LL, 0LL, 4LL, 3, 68LL);
}


/*****************************
 * Interface
 * ***************************/
guint vendor_qti_ims_sms_send(BinderExtSms* ext, const char* smsc, const void* pdu,
    gsize pdu_len, guint msg_ref, BINDER_EXT_SMS_SEND_FLAGS flags,
    BinderExtSmsSendFunc complete, GDestroyNotify destroy,
    void* user_data);
void vendor_qti_ims_sms_cancel(BinderExtSms* ext, guint id);
void vendor_qti_ims_sms_ack_report(BinderExtSms* ext, guint msg_ref, gboolean ok);
void vendor_qti_ims_sms_ack_incoming(BinderExtSms* ext, gboolean ok);
gulong vendor_qti_ims_sms_add_report_handler(BinderExtSms* ext,
    BinderExtSmsReportFunc handler, void* user_data);
gulong vendor_qti_ims_sms_add_incoming_handler(BinderExtSms* ext,
    BinderExtSmsIncomingFunc handler, void* user_data);
void vendor_qti_ims_sms_remove_handler(BinderExtSms* ext, gulong id);


static void qti_ims_sms_iface_init(BinderExtSmsInterface* iface){
    iface->flags |= BINDER_EXT_SMS_INTERFACE_FLAG_IMS_SUPPORT | BINDER_EXT_SMS_INTERFACE_FLAG_IMS_REQUIRED;
    iface->version = 1;
    iface->send = vendor_qti_ims_sms_send;
    iface->cancel = vendor_qti_ims_sms_cancel;
    iface->ack_report = vendor_qti_ims_sms_ack_report;
    iface->ack_incoming = vendor_qti_ims_sms_ack_incoming;
    iface->add_report_handler = vendor_qti_ims_sms_add_report_handler;
    iface->add_incoming_handler = vendor_qti_ims_sms_add_incoming_handler;
    iface->remove_handler = vendor_qti_ims_sms_remove_handler;
}


BinderExtSms* vendor_qti_ims_sms_new(VendorQtiImsRadio* ims_radio,VendorQtiImsStateObject* ims_state){
    VendorQtiImsSms* sms= g_object_new(QTI_TYPE_SMS, NULL);
    
    sms->ims_state = ims_state; // 不是直接赋值
    sms->ims_radio = ims_radio; // 不是直接赋值
    // TODO绑定信号  qti-ims-radio-incoming-sms qti-ims-radio-sms-status-report

    return BINDER_EXT_IMS(sms);
}