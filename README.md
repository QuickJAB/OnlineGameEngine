# OnlineGameEngine

## Brief Description

This is a hobby C++ experimentation repo for learning how best to structure a modular game engine for use in online-multiplayer games. It focuses primarily on data structure and how to send that data over a network while accounting for packet loss and optimising for bandwidth. The demo games should also have a large focus on client-side prediction to ensure they feel smooth and responsive.

### Contents

- A small game engine for online-multiplayer and singleplayer games.
- A demo online-multiplayer game using a headless server with connected clients

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