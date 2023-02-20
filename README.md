# Dat Engine
As the description clearly states, this is a toy engine that I work on in my free time. It is not a game engine substitute.

# Getting Started

As of the current version, DatEngine doesn't support any form of project generation. As soon as I figure out how to set up CMake or Premake, I'll do so. 
For now, opening the [Visual Studio](https://visualstudio.microsoft.com/pt-br/downloads/) solution file will have to suffice.

## Prerequisites

In order to build this project, you need CMake.

- [CMake](https://cmake.org/download/)

## Downloading

It is advised to clone the repository using the following command:

```bash
git clone --recurse-submodules https://github.com/DatDarkAlpaca/dat-engine/
```

If you cloned it right away and you're facing problems with the vendor files, just execute the following command:

```bash
git submodule update --init --recursive
```

## Building the project

Use whatever IDE you want to configure and build the project. The CMake files will take care of the DLL copying, so it should run without much hassle.

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT) - see the [LICENSE](LICENSE) file for details


