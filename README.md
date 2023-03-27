# DRC Sensorbar

This plugin for the [WiiUPluginSystem](https://github.com/wiiu-env/WiiUPluginSystem) enables the sensor bar of the
GamePad (DRC) permanently.

## Limitations

- The sensor bar is turned off when opening the HOME menu or when the GamePad is disconnected. It gets re-enabled when the HOME menu is closed/the GamePad is connected again. This is a system limitation and expected behaviour
- Does not work in applets like the web browser - this is a limitation of the Plugin System
- While using, remember that the cursor is not always shown on the GamePad - you should maybe use this together with
  another plugin, that can swap the screens (depending on the game/app)

## Installation

1. Install Aroma
2. Check the Releases page and download the [latest non-preview version](https://github.com/WiiDatabase/DRC-Sensorbar/releases/latest) of this plugin
3. Extract it to "`SD://wiiu/environments/aroma/plugins`"
4. Done!
5. You can disable the plugin via the WUPS Config Menu ("L" + "D-Pad Down" + "Minus")

## Building

For building you need:

- [wups](https://github.com/Maschell/WiiUPluginSystem)
- [wut](https://github.com/devkitpro/wut)

Install them (in this order) according to their README's. Don't forget the dependencies of the libs itself.

Then you should be able to compile via `make` (with no logging) or `make DEBUG=1` (with logging).

## Buildflags

### Logging

Building via `make` only logs errors (via OSReport). To enable logging via the [LoggingModule](https://github.com/wiiu-env/LoggingModule) set `DEBUG` to `1` or `VERBOSE`.

`make` Logs errors only (via OSReport).  
`make DEBUG=1` Enables information and error logging via [LoggingModule](https://github.com/wiiu-env/LoggingModule).  
`make DEBUG=VERBOSE` Enables verbose information and error logging via [LoggingModule](https://github.com/wiiu-env/LoggingModule).

If the [LoggingModule](https://github.com/wiiu-env/LoggingModule) is not present, it'll fallback to UDP (Port 4405) and [CafeOS](https://github.com/wiiu-env/USBSerialLoggingModule) logging.

## Building using the Dockerfile

It's possible to use a docker image for building. This way you don't need anything installed on your host system.

```
# Build docker image (only needed once)
docker build . -t drc-sensorbar-builder

# make
docker run -it --rm -v ${PWD}:/project drc-sensorbar-builder make DEBUG=1

# make clean
docker run -it --rm -v ${PWD}:/project drc-sensorbar-builder make clean
```

## Format the code via docker

`docker run --rm -v ${PWD}:/src ghcr.io/wiiu-env/clang-format:13.0.0-2 -r ./src -i`
