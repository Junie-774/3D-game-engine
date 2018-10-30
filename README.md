# SpaceBois

Personal video game engine project

It's currently a 3D Environment with Maya from borderlands. You can move around with WASD, Left-shift for going down, space for going up. 

Uses OpenGL for drawing and GLFW for window handling

Provides useful/convenient abstractions around OpenGL and GLFW

Provides Resource managing capabilities for shader files and textures

Can load models, but this isn't super robust, so it might not work for your model

# Compiling/running:
This is linux only, sorry if you're on another platform and want to use this

1. Download the source, and edit CMakelists.txt, on the line:

`target_link_libraries(${PROJECT_NAME} GLX_nvidia)
	
Change GLX_nvidia to your computer's OpenGL driver library. this is usually found in /usr/lib/

2. Set up build using cmake

`cd SpaceBois
`cmake bin

3. Compile the project

`cd bin
`make

4. Run the executable in cmake-build-debug!

` ./SpaceBois

