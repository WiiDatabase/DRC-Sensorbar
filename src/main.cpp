#include "main.h"
#include "utils/logger.h"
#include <vpad/input.h>
#include <wups.h>
#include <wups/config/WUPSConfigItemBoolean.h>

WUPS_PLUGIN_NAME("DRC-Sensorbar");
WUPS_PLUGIN_DESCRIPTION("Enables the sensorbar of the Wii U GamePad permanently.");
WUPS_PLUGIN_VERSION(VERSION_FULL);
WUPS_PLUGIN_AUTHOR("WiiDatabase.de");
WUPS_PLUGIN_LICENSE("MIT");
WUPS_USE_STORAGE("drc_sensorbar");

#define CONFIG_ID_SENSORBAR_ENABLED "enabled"

bool sEnabled                               = true;
constexpr bool CONFIG_ENABLED_DEFAULT_VALUE = true;

void enabledChanged(ConfigItemBoolean *item, bool newValue) {
    DEBUG_FUNCTION_LINE("New value in enabledChanged: %d", newValue);
    sEnabled = newValue;
    WUPSStorageAPI::Store(item->identifier, sEnabled);

    if (sEnabled) {
        VPADSetSensorBar(VPAD_CHAN_0, true);
    } else {
        VPADSetSensorBar(VPAD_CHAN_0, false);
    }
}

WUPSConfigAPICallbackStatus ConfigMenuOpenedCallback(WUPSConfigCategoryHandle rootHandle) {
    WUPSConfigCategory root = WUPSConfigCategory(rootHandle);

    try {
        auto settingsCat = WUPSConfigCategory::Create("Settings");

        settingsCat.add(WUPSConfigItemBoolean::Create(CONFIG_ID_SENSORBAR_ENABLED, "Enable GamePad Sensorbar",
                                                      CONFIG_ENABLED_DEFAULT_VALUE, sEnabled,
                                                      enabledChanged));
        root.add(std::move(settingsCat));
    } catch (std::exception &e) {
        DEBUG_FUNCTION_LINE_ERR("Creating config menu failed: %s", e.what());
        return WUPSCONFIG_API_CALLBACK_RESULT_ERROR;
    }

    return WUPSCONFIG_API_CALLBACK_RESULT_SUCCESS;
}

void ConfigMenuClosedCallback() {
    WUPSStorageAPI::SaveStorage();
}

INITIALIZE_PLUGIN() {
    initLogging();

    WUPSConfigAPIOptionsV1 configOptions = {.name = "DRC-Sensorbar"};
    if (WUPSConfigAPI_Init(configOptions, ConfigMenuOpenedCallback, ConfigMenuClosedCallback) != WUPSCONFIG_API_RESULT_SUCCESS) {
        DEBUG_FUNCTION_LINE_ERR("Failed to init config api");
    }

    WUPSStorageError storageRes;
    if ((storageRes = WUPSStorageAPI::GetOrStoreDefault(CONFIG_ID_SENSORBAR_ENABLED, sEnabled, CONFIG_ENABLED_DEFAULT_VALUE)) != WUPS_STORAGE_ERROR_SUCCESS) {
        DEBUG_FUNCTION_LINE_ERR("GetOrStoreDefault failed: %s (%d)", WUPSStorageAPI_GetStatusStr(storageRes), storageRes);
    }
    if ((storageRes = WUPSStorageAPI::SaveStorage()) != WUPS_STORAGE_ERROR_SUCCESS) {
        DEBUG_FUNCTION_LINE_ERR("GetOrStoreDefault failed: %s (%d)", WUPSStorageAPI_GetStatusStr(storageRes), storageRes);
    }

    deinitLogging();
}

ON_APPLICATION_START() {
    initLogging();
    if (sEnabled) {
        VPADSetSensorBar(VPAD_CHAN_0, true);
    }
}

ON_APPLICATION_ENDS() {
    deinitLogging();
}
