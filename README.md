<div align="center">
  
  [![Commit Activity](https://img.shields.io/github/commit-activity/w/Generalisk/GeneSource-SDK)](https://github.com/Generalisk/GeneSource-SDK)
  [![Commit Activity](https://img.shields.io/github/commit-activity/m/Generalisk/GeneSource-SDK)](https://github.com/Generalisk/GeneSource-SDK)
  [![Commit Activity](https://img.shields.io/github/commit-activity/y/Generalisk/GeneSource-SDK)](https://github.com/Generalisk/GeneSource-SDK)
  [![Commit Activity](https://img.shields.io/github/commit-activity/t/Generalisk/GeneSource-SDK)](https://github.com/Generalisk/GeneSource-SDK)
  
  <!--[![License](https://img.shields.io/github/license/Generalisk/GeneSource-SDK)](https://github.com/Generalisk/GeneSource-SDK/blob/main/LICENSE)-->
  [![Issues](https://img.shields.io/github/issues/Generalisk/GeneSource-SDK)](https://github.com/Generalisk/GeneSource-SDK/issues)
  [![File Size](https://img.shields.io/github/repo-size/Generalisk/GeneSource-SDK)](https://github.com/Generalisk/GeneSource-SDK)
  [![Last Commit](https://img.shields.io/github/last-commit/Generalisk/GeneSource-SDK)](https://github.com/Generalisk/GeneSource-SDK)
  
  [![Repo Watchers](https://img.shields.io/github/watchers/Generalisk/GeneSource-SDK)](https://github.com/Generalisk/GeneSource-SDK)
  [![Repo Stars](https://img.shields.io/github/stars/Generalisk/GeneSource-SDK)](https://github.com/Generalisk/GeneSource-SDK)
  [![Repo Forks](https://img.shields.io/github/forks/Generalisk/GeneSource-SDK)](https://github.com/Generalisk/GeneSource-SDK)
</div>

<div align="center">
  
  # GeneSource SDK
</div>

The GeneSource SDK is A community-ran branch of Valve's [Source SDK](https://github.com/ValveSoftware/source-sdk-2013) which expands on it with new features, bug fixes, and quality of life improvements.

# Contents
- [Features](#features)
- [Supported Games](#supported-games)
- [Requirements](#requirements)
  - [For Windows Users](#for-windows-users)
  - [For Linux Users](#for-linux-users)
- [Installing the Repo](#installing-the-repo)
  - [Method 1](#method-1)
  - [Method 2](#method-2)
  - [Method 3](#method-3)
- [Compiling](#compiling)
  - [Windows](#windows)
  - [Linux](#linux)
- [Licensing](#licensing)
- [Credits](#credits)
- [Contributing](#contrinuting)
- [Useful Resources](#useful-resources)

# Features
- A built-in library of free-to-use assets made by the community, for the community
- Discord RPC Support
- Proximity Chat Support
- Support for animated Steam Avatars
- ...and ***SO MANY*** bug fixes & quality of life improvements

# Supported Games
- Half-Life 2
- Half-Life 2: Deathmatch
- Team Fortress 2

# Requirements
- [Steam](https://store.steampowered.com/about)
- [Source SDK Base 2013 Multiplayer](https://steamdb.info/app/243750)
- [Python 3.13+](https://www.python.org/downloads/windows)
## For Windows Users
- [Visual Studio 2022](https://visualstudio.microsoft.com/vs/community)
  - `MSVC v143 - VS 2022 C++ x64/x86 build tools (Latest)`
  - `Windows 11 SDK (10.0.22621.0)`/`Windows 10 SDK (10.0.19041.1)`
## For Linux Users
- [podman](https://podman.io/)

# Installing the Repo
There are multiple ways to set up this repo on your computer:
## Method 1
> [!WARNING]
> You will not be able to push commits/pull requests through directly if you use this method.
- At the top of the Repos' home page, click on the green button labeled `Code`.
- At the bottom of the panel that just popped up, click on the button labeled `Download ZIP`.
- Once the zip file has finished downloading, extract it's contents wherever you want.
## Method 2
> [!NOTE]
> This method requires [Git](https://git-scm.com/downloads) to be installed!
- Enter this command inside your Powershell/Terminal at the directory of your choice:
  ```
  git clone https://github.com/Generalisk/GeneSource-SDK.git
  ```
## Method 3
> [!NOTE]
> This method requires [Github Desktop](https://desktop.github.com/) to be installed!
- Open your repository list and click on `Add > Clone repository...`
- Go to the URL tab.
- Enter `Generalisk/GeneSource-SDK` into the box and set the local path to wherever you want.

# Compiling
## Windows
- Inside the `src` directory, run:
  ```
  createallprojects.bat
  ```
  This will refresh the Visual Studio Project Files with any changes you have made to the VPC scripts and will generate new project files if they don't exist.
- Open the Solution (`everything.sln`) in Visual Studio.
- Make sure that the Platform Configuration is set to `Release` instead of `Debug`.
- In the menu, go to `Build -> Build Solution` or press `Ctrl + Shift + B`.
  - Alternatively, press `F5` or click the `Local Windows Debugger` button with the Green Arrow to start debugging inside of Visual Studio.
## Linux
- Inside the `src` directory, run:
  ```
  ./buildallprojects
  ```
  This will compile your project automatically against the Steam Runtime.

# Licensing
This SDK and all projects stemming from it are licenced under the `Source 1 SDK License`, more info can be found [here](LICENSE).

To receive A commercial license for the SDK, reach out to valve to negotiate on recieving a commercial license.

For more info on distributing your mod on steam, check out [here](https://partner.steamgames.com/doc/sdk/uploading/distributing_source_engine).

# Credits
- [Source SDK](https://developer.valvesoftware.com/wiki/SDK2013_GettingStarted) by [Valve Software](https://www.valvesoftware.com/)
- [List of Contributors](.github/CONTRIBUTORS.md)

# Contributing
Before you go and make A pull request, please make sure that your request follows our [Contributon Guidelines](.github/CONTRIBUTING.md).

# Useful Resources
- [Valve Developer Wiki](https://developer.valvesoftware.com/wiki/Setting_up_Source_SDK_Base_2013_Multiplayer)
- [Valve Developer Community Discord Server](https://discord.gg/AC8254CJax)
