#include <wups.h>
#include <string.h>

#include <nsysnet/socket.h>
#include <vpad/input.h>
#include <utils/logger.h>

WUPS_PLUGIN_NAME("DRC Sensorbar");
WUPS_PLUGIN_DESCRIPTION("Permanently enables the GamePad's sensorbar.");
WUPS_PLUGIN_VERSION("v1.0");
WUPS_PLUGIN_AUTHOR("Brawl");
WUPS_PLUGIN_LICENSE("MIT");

ON_APPLICATION_START(args){
   socket_lib_init();
   log_init();

   DEBUG_FUNCTION_LINE("Init of drc-sensorbar!\n");
   VPADSetSensorBar(0, true);
}
