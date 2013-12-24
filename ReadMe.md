SquareCubed InDev 0.3.0
=======================
SquareCubed is a 2D OpenGL Multiplayer game engine written
in C++. Designed for both quick prototyping and full release
games, SquareCubed aims to create an extensive diverse and
extensible toolkit for creating 2D multiplayer games.

The engine is open source to allow people to freely
contribute to the development of this project and to allow
people to use the engine in their own software projects.

If you find this file locally or part of another project, go
to the [official github page](https://github.com/LaylConway/SquareCubed/)
for the latest version. If a project is using SquareCubed in
a way that doesn't comply with the license granted to that
project, please notify [EdgeWorks Games](http://edgeworksgames.com/home/contact)&trade;
so we can contact the project maintainer.

Build Requirements
------------------
- C++11 Compatible Compiler (Visual Studio 2013 or later)
- CMake 2.8.3 or Later

Dependencies
------------
You can download a package of precompiled dependencies for VC++ 2013 [here](https://dl.dropboxusercontent.com/u/69844866/Dependencies.zip).
This package does not include CoherentUI and RakNet which must be manually licensed and downloaded.
RakNet has an online automated form for requesting a indie license.
CoherentUI has an online evaluation request form.
- GLFW
- GLEW
- DevIL
- RakNet
- CoherentUI

Build Guide
-----------
This guide is for Visual Studio 2013. If you are on a different platform or using a different compiler you will have to manually make a dependency folder for your target.
1. Download and unzip the dependency package.
2. Place CoherentUI in the dependency folder in a folder "CoherentUI".
3. Place RakNet in the dependency folder in a folder "raknet".
4. Run CMake and fill in the dependency folder in the settings.
5. If CMake does not report any problems, you can now generate a project file and build the game.

Licenses
--------
This copy of SquareCubed is released All Rights Reserved.
Do not redistribute in any way, including but not limited
to binary form. This page (and License.txt) will be updated
once we find a more permissive license that fits our aims
for this project.

Contact [EdgeWorks Games](http://EdgeWorksGames.com/Home/Contact)&trade; for commercial licensing.