#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "Component/Camera.h"
#include "Command.h"
#include "ControlCamera.h"
#include "GameObject.h"
#include "GameObjectDrawer.h"
#include "OpenGL/GLMesh.h"
#include "OpenGL/GLMeshDrawer.h"
#include "Component/PhysicsBody.h"
#include "PointLight.h"
#include "Prefab.h"
#include "Scripts/PlayerMovement.h"
#include "ResourceManager.h"
#include "SBWindow.h"
#include "Transform.h"
#include "OpenGL/GLVertex.h"
#include <glm/gtx/string_cast.hpp>


int main() {

    SBWindow win("SpaceBoisTMP", {1000, 1000});
    win.setActive();
    glm::mat4 proj = glm::perspective(45.0f, 1000.0f/ 1000.0f, 0.01f, 100.0f);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err!=GLEW_OK) {
        std::cout << "glewInit failed: " << glewGetErrorString(err) << "\n";
        return -1;
    };

    InputManager in(win);

    ResourceManager man;
    ShaderProgram program(man.loadFileContents("vertexshader.glsl"), man.loadFileContents("fragmentshader.glsl"));
    program.setUniformValue("proj", proj);
    glEnable(GL_DEPTH_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLMeshDrawer renderer;
    GameObjectDrawer drawer;

    Model mayaModel = ResourceManager::loadModelFromFile("../Maya/maya.obj");

    std::vector<std::reference_wrapper<Command>> cmds;


    GameObject player("PLAYER");
    player.addComponents(Camera(player), PhysicsBody(player));

    Prefab cubeFab;
    GameObject maya = cubeFab.generate("MAYA");
    maya.setModel(std::move(mayaModel));

    //Prefab<Camera, PhysicsBody> playerFab;
    //GameObject player (playerFab.generate("PLAYER"));

    player.addScript(PlayerMovement(player, in));
    player.addScript(ControlCamera(
            player.getComponent<Camera>().value(),
            in)
            );

    glm::vec3 initPos(-2.0f, 1.5f, 2.0f);

    player.getTransform().setPosition(initPos);
    player.getComponent<Camera>()->get().lookAt(glm::vec3(0.0f, 0.0f, 0.0f));

    PointLight light("Light", program);
    light.getTransform().setPosition(initPos);
    light.intensity = 0.75f;
    light.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    while (!win.shouldClose()) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        Time::instance().update();

        in.fillCommandQueue(cmds);
        for (auto cmd : cmds) {
            cmd.get().execute();
        }

        maya.getTransform().rotate(0.5f * Time::instance().deltaTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        player.update();
        light.update();

        auto& cam = player.getComponent<Camera>()->get();
        program.setUniformValue("view", cam.getViewMat());

        drawer.draw(maya, renderer, program);

        win.update();

        cmds.clear();

        if (auto i = glGetError()) {
            std::cout << "GL Error: " << i << "\n";
        }
    }

    return 0;
}