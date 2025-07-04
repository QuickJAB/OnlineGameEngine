# OnlineGameEngine

## Brief Description

This is a hobby project intended for me to learn more about creating the necessary engine and game code for an online game using a client and a headless server.

## Build information

### Supported development platforms

- Windows

### Build system

Premake5. The .exe and license are provided in this repo under Externals/premake

### Steps

1. If you don't have premake5 setup, add the path to the provided version to your 'PATH' environment variable
2. If you are using VS2022 then run generateProjectFiles.bat, otherwise you must first modify the .bat to your preferred VS version
3. Build the solution using VS2022 or your preferred version

## External dependencies

All of these dependencies are provided in this repo.

- SDL3: Windowing, rendering, event handling and audio
- ENet: Socketing