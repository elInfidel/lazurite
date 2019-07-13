# Lazurite

## Building the Project

The project compiles with Visual Studio 2017. Ensure you have windows SDK 10.0.17763.0. Binaries and headers files for any
third party dependencies listed below are provided in the repository. I'm targeting Windows x64 and as such any other platform
configuration will require you to recompile for your own needs.

### External Libraries

* GLFW      - https://www.glfw.org/
* Assimp    - http://www.assimp.org/
* STB       - https://github.com/nothings/stb
* GLM       - https://glm.g-truc.net/

## Goals
I use Lazurite as a playground for testing the implementation of common techniques and patterns in game development. If you decide you want 
to get the code running and somehow do (See above) you do so at your own risk, I'm not liable if your computer grows arms and punches you in the face.

Currently I'm playing with the following
* Component based architecture
* Embedded scripting languages (Can we embed V8 and get typescript compiling into the framework?)
* Subsystems & services