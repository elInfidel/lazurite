# Lazurite

## Building the Project
Source for fmod and physx are both restricted by EULA. I store my code here for easier management
and as such it isn't intended to be downloaded by others and run. However if you want to have a gamble at getting it to run you
could try adding the header files and lib files to your project on your own. Headers are stored in Includes/fmod or Includes/physx
and libraries Libraries/fmod or Libraries/physx. You'll also need to place any relevant dll files into the location of the
binaries.

## Goals
I use Lazurite as a playground for testing the implementation of common techniques and patterns in game development.
By no means is it an engine I would use to build a game, it's likely full of performance issues I haven't taken into
consideration, nor does it even possess the required functionality for a full scale game anyway. If you decide you want to get the code running and somehow do (See above) you do so at your own risk, I'm
not liable if your computer grows legs and jumps off of your balcony as a side effect of executing this built code.

Currently I'm playing with the following
* Component based architecture
* Scene graphs
* Physics integration
* Shading
