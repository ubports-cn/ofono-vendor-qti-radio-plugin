#include "vendor_qti_ext.h"

#include <ofono/log.h>
#include <ofono/plugin.h>
#include <binder_ext_plugin.h>

/*==========================================================================*
 * QTI plugin
 *==========================================================================*/
extern const char qti_plugin_name[];

// sub_B940
static int vendor_qti_plugin_init(void){

  BinderExtPlugin* plugin = vendor_qti_ext_new();

  binder_ext_plugin_register(plugin);
  binder_ext_plugin_unref(plugin);
  return 0;
}
// sub_B8F8
static void vendor_qti_plugin_exit(void){
  binder_ext_plugin_unregister(qti_plugin_name);
}

OFONO_PLUGIN_DEFINE(vendor_qti, "Vendor QTI plugin", OFONO_VERSION,
                    OFONO_PLUGIN_PRIORITY_DEFAULT, vendor_qti_plugin_init, vendor_qti_plugin_exit)

