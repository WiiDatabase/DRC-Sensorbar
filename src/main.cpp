#include <vpad/input.h>
#include <wups.h>

WUPS_PLUGIN_NAME("DRC-Sensorbar");
WUPS_PLUGIN_DESCRIPTION(
    "Enables the sensorbar of the Wii U GamePad permanently.");
WUPS_PLUGIN_VERSION("v2.0");
WUPS_PLUGIN_AUTHOR("WiiDatabase.de");
WUPS_PLUGIN_LICENSE("MIT");

ON_APPLICATION_START() { VPADSetSensorBar(VPAD_CHAN_0, true); }
