#include "vendor_qti_ext.h"
#include "vendor_qti_slot.h"

#include "binder_ext_plugin_impl.h"

#include "binder_ext_ims.h"
#include "binder_ext_slot_impl.h"

/*==========================================================================*
 * QTI ext
 *==========================================================================*/

typedef BinderExtPluginClass VendorQtiExtClass;
typedef struct qti_plugin {
    BinderExtPlugin parent;
    void* b_40;
    int num;

} VendorQtiExt;

GType qti_plugin_get_type();
G_DEFINE_TYPE(VendorQtiExt, qti_plugin, BINDER_EXT_TYPE_PLUGIN)

#define THIS_TYPE qti_plugin_get_type()
#define THIS(obj) G_TYPE_CHECK_INSTANCE_CAST(obj, THIS_TYPE, VendorQtiExt)

static const char qti_plugin_name[] = "qti";

/*==========================================================================*
 * BinderExtPluginClass
 *==========================================================================*/
static
BinderExtSlot*
qti_plugin_new_slot(
    BinderExtPlugin* plugin,
    RadioInstance* radio,
    GHashTable* params)
{
    return vendor_qti_slot_new(radio, params);
}

/*==========================================================================*
 * API
 *==========================================================================*/
BinderExtPlugin* vendor_qti_ext_new()
{
    return g_object_new(THIS_TYPE, NULL);
}

/*==========================================================================*
 * Internals
 *==========================================================================*/
static
void
qti_plugin_init(
    VendorQtiExt* self)
{
}

static
void
qti_plugin_class_init(
    VendorQtiExtClass* klass)
{
    klass->plugin_name = qti_plugin_name;
    klass->new_slot = qti_plugin_new_slot;
}

/**
 * VendorQtiExt
 * VendorQtiIms
 * VendorQtiImsCall
 * VendorQtiImsConfObject
 * VendorQtiImsRadio
 * VendorQtiImsSms
 * VendorQtiImsStateObject
 * VendorQtiSlot
 * 
 * 
 * */
