#include "main.h"
#include "utils/logger.h"
#include <vpad/input.h>
#include <wups.h>
#include <wups/config/WUPSConfigItemBoolean.h>

WUPS_PLUGIN_NAME("DRC-Sensorbar");
WUPS_PLUGIN_DESCRIPTION(
        "Enables the sensorbar of the Wii U GamePad permanently.");
WUPS_PLUGIN_VERSION(VERSION_FULL);
WUPS_PLUGIN_AUTHOR("WiiDatabase.de");
WUPS_PLUGIN_LICENSE("MIT");
WUPS_USE_STORAGE("drc_sensorbar");

#define CONFIG_ID_SENSORBAR_ENABLED "enabled"
bool enabled = true;


INITIALIZE_PLUGIN() {
    initLogging();
    DEBUG_FUNCTION_LINE("INITIALIZE_PLUGIN of example_plugin!");

    WUPSStorageError storageRes = WUPS_OpenStorage();
    if (storageRes != WUPS_STORAGE_ERROR_SUCCESS) {
        DEBUG_FUNCTION_LINE("Failed to open storage %s (%d)", WUPS_GetStorageStatusStr(storageRes), storageRes);
    } else {
        if ((storageRes = WUPS_GetBool(nullptr, CONFIG_ID_SENSORBAR_ENABLED, &enabled)) == WUPS_STORAGE_ERROR_NOT_FOUND) {
            if (WUPS_StoreBool(nullptr, CONFIG_ID_SENSORBAR_ENABLED, enabled) != WUPS_STORAGE_ERROR_SUCCESS) {
                DEBUG_FUNCTION_LINE("Failed to store bool");
            }
        } else if (storageRes != WUPS_STORAGE_ERROR_SUCCESS) {
            DEBUG_FUNCTION_LINE("Failed to get bool %s (%d)", WUPS_GetStorageStatusStr(storageRes), storageRes);
        }

        if (WUPS_CloseStorage() != WUPS_STORAGE_ERROR_SUCCESS) {
            DEBUG_FUNCTION_LINE("Failed to close storage");
        }
    }
    deinitLogging();
}

WUPS_CONFIG_CLOSED() {
    // Save all changes
    if (WUPS_CloseStorage() != WUPS_STORAGE_ERROR_SUCCESS) {
        DEBUG_FUNCTION_LINE_ERR("Failed to close storage");
    }
}

ON_APPLICATION_START() {
    initLogging();
    if (enabled) {
        VPADSetSensorBar(VPAD_CHAN_0, true);
    }
}

ON_APPLICATION_ENDS() {
    deinitLogging();
}

void enabledChanged(ConfigItemBoolean *item, bool newValue) {
    DEBUG_FUNCTION_LINE_INFO("New value in enabledChanged: %d", newValue);
    enabled = newValue;
    WUPS_StoreInt(nullptr, CONFIG_ID_SENSORBAR_ENABLED, enabled);

    if (enabled) {
        VPADSetSensorBar(VPAD_CHAN_0, true);
    } else {
        VPADSetSensorBar(VPAD_CHAN_0, false);
    }
}

WUPS_GET_CONFIG() {
    if (WUPS_OpenStorage() != WUPS_STORAGE_ERROR_SUCCESS) {
        DEBUG_FUNCTION_LINE("Failed to open storage");
        return 0;
    }

    WUPSConfigHandle config;
    WUPSConfig_CreateHandled(&config, "DRC-Sensorbar");

    WUPSConfigCategoryHandle cat;
    WUPSConfig_AddCategoryByNameHandled(config, "Settings", &cat);

    WUPSConfigItemBoolean_AddToCategoryHandled(
            config, cat, CONFIG_ID_SENSORBAR_ENABLED, "Enable GamePad Sensorbar", enabled,
            &enabledChanged);

    return config;
}
