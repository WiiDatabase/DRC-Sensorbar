DRC Sensorbar
===============
This plugin for the [WiiUPluginSystem](https://github.com/Maschell/WiiUPluginSystem) enables the sensor bar of the GamePad (DRC) permanently.

## Limitations
* The sensor bar is turned off when opening the HOME menu or when the GamePad is disconnected. It gets re-enabled when the HOME menu is closed/the GamePad is connected again. This is a system limitation and expected behaviour
* Does not work in applets like the web browser - this is a limitation of the Plugin System
* While using, remember that the cursor is not always shown on the GamePad - you should maybe use this together with the SwipSwapMe plugin (depending on the game/app)

## Installation
1. Install the [WiiUPluginLoader](https://github.com/Maschell/WiiUPluginLoader/releases)
2. Check the Releases page and download the latest version of this plugin
3. Extract it to "SD://wiiu/plugins/"
4. Done! Now start WUPS through the Wii U Homebrew Launcher and activate the plugin

## Building
For building you need:
- [wups](https://github.com/Maschell/WiiUPluginSystem)
- [wut](https://github.com/decaf-emu/wut)
- [libutils](https://github.com/Maschell/libutils/tree/wut) for common functions (WUT version).

Install them (in this order) according to their README's. Don't forget the dependencies of the libs itself.
