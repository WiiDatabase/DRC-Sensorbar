DRC Sensorbar
===============
This plugin for the [WiiUPluginSystem](https://github.com/wiiu-env/WiiUPluginSystem) enables the sensor bar of the
GamePad (DRC) permanently.

## Limitations
* The sensor bar is turned off when opening the HOME menu or when the GamePad is disconnected. It gets re-enabled when the HOME menu is closed/the GamePad is connected again. This is a system limitation and expected behaviour
* Does not work in applets like the web browser - this is a limitation of the Plugin System
* While using, remember that the cursor is not always shown on the GamePad - you should maybe use this together with
  another plugin, that can swap the screens (depending on the game/app)

## Installation

1. Install Aroma
2. Check the Releases page and download the [latest non-preview version](https://github.com/WiiDatabase/DRC-Sensorbar/releases/latest) of this plugin
3. Extract it to "SD://wiiu/environments/aroma/plugins"
4. Done!

## Building
For building you need:

- [wups](https://github.com/wiiu-env/WiiUPluginSystem)
- [wut](https://github.com/devkitPro/wut)
