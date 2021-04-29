# Lazurite

## Building the Project

The project uses CMAKE, you may generate project files for your environment of choice. Third party libraries are imported via cmake using git tags. I'm targeting Windows x64 and as such any other platform
configuration will require you to recompile for your own needs.

### External Libraries

-   GLFW - https://www.glfw.org/
-   Assimp - http://www.assimp.org/
-   STB - https://github.com/nothings/stb
-   GLM - https://glm.g-truc.net/

## TODO

GLTFLoader::ProcessMesh - Need to actually read vertex and indice data so it can be loaded into Primitive objected and constructed on the GPU.

## Goals

I use Lazurite as a playground for testing the implementation of common techniques and patterns in game development. If you decide you want
to get the code running and somehow do (See above) you do so at your own risk, I'm not liable if your computer grows arms and punches you in the face.

Currently I'm playing with the following

-   Component based architecture
-   Embedded scripting languages (Can we embed V8 and get typescript compiling into the framework?)
-   Subsystems & services
-   Physically based rendering
-   Transparent object sorting/rendering
