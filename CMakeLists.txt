cmake_minimum_required(VERSION 3.10)
project(SpaceBois)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_SOURCES
        main.cpp
        Transform.cpp
        SBWindow.cpp SBWindow.h Command.cpp Command.h InputManager.cpp InputManager.h ShaderProgram.cpp ShaderProgram.h ResourceManager.cpp ResourceManager.h OpenGL/GLMesh.cpp OpenGL/GLMesh.h OpenGL/GLVertex.h OpenGL/GLMeshDrawer.cpp OpenGL/GLMeshDrawer.h OpenGL/GLTexture.cpp OpenGL/GLTexture.h Component/Camera.cpp Component/Camera.h GameObject.cpp GameObject.h Time.cpp Time.h Component/PhysicsBody.cpp Component/PhysicsBody.h Scripts/Script.cpp Scripts/Script.h Scripts/PlayerMovement.cpp Scripts/PlayerMovement.h Component/Component.cpp Component/Component.h Scripts/ControlCamera.cpp Scripts/ControlCamera.h Game.cpp Game.h Material.cpp Material.h PointLight.cpp PointLight.h Keyboard.cpp Keyboard.h Model.cpp Model.h OpenGL/GLBuffer.cpp OpenGL/GLBuffer.h GameObjectDrawer.cpp GameObjectDrawer.h Prefab.cpp Prefab.h Vertex.h Mesh.cpp Mesh.h Face.cpp Face.h)

set(PROJECT_HEADERS
        Transform.h)

include_directories(.)
include_directories(Scripts)

add_executable(SpaceBois ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} GLEW)
target_link_libraries(${PROJECT_NAME} GLX_nvidia)
target_link_libraries(${PROJECT_NAME} SOIL)
target_link_libraries(${PROJECT_NAME} assimp)
