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

    SBWindow win("SpaceBoisTMP");
    win.setActive();

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err!=GLEW_OK) {
        std::cout << "glewInit failed: " << glewGetErrorString(err) << "\n";
        return -1;
    };

    InputManager in(win);

    ResourceManager man;
    auto msg = man.loadFileContents("balls.txt");

    CustomCommand d([&msg](){std::cout << msg; });

    std::vector<GLVertex> vertices = {
                                    {{0.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
                                    {{0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
                                    {{0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
                                    {{0.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},

                                    {{0.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
                                    {{1.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
                                    {{0.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
                                    {{1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},

                                    {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
                                    {{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
                                    {{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
                                    {{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},

                                    {{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
                                    {{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
                                    {{1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
                                    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},

                                    {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
                                    {{1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
                                    {{0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
                                    {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},

                                    {{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
                                    {{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
                                    {{0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
                                    {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    };

    for (auto& v : vertices) {
        v.position -= glm::vec3(0.5f, 0.5f, 0.5f);
    }

    std::vector<GLuint> indices = {0, 1, 2, 2, 1, 3,
                                   4, 5, 6, 6, 5, 7,
                                   8, 9, 10, 10, 9, 11,
                                   12, 13, 14, 14, 13, 15,
                                   16, 17, 18, 18, 17, 19,
                                   20, 21, 22, 22, 21, 23
                                   };

    man.addTexture("tiger", "background.png", false);
    Material mat;

    GLMeshDrawer renderer;
    GameObjectDrawer drawer;

    Model shit = ResourceManager::loadModelFromFile("../Maya/maya.obj");

    ShaderProgram program(man.loadFileContents("vertexshader.glsl"), man.loadFileContents("fragmentshader.glsl"));
    glEnable(GL_DEPTH_TEST);

    std::vector<std::reference_wrapper<Command>> cmds;

    glm::mat4 proj = glm::perspective(45.0f, 1000.0f/ 1000.0f, 0.01f, 100.0f);

    glm::vec3 pos(-2.0f, 1.5f, 2.0f);

    GameObject player("PLAYER");
    player.addComponents(Camera(player), PhysicsBody(player));

    Prefab cubeFab;
    GameObject maya = cubeFab.generate("MAYA");
    maya.setModel(std::move(shit));

    //Prefab<Camera, PhysicsBody> playerFab;
    //GameObject player (playerFab.generate("PLAYER"));

    player.addScript(PlayerMovement(player, in));
    player.addScript(ControlCamera(
            player.getComponent<Camera>().value(),
            in)
            );

    player.getTransform().setPosition(pos);
    player.getComponent<Camera>()->get().lookAt(glm::vec3(0.0f, 0.0f, 0.0f));

    program.setUniformValue("proj", proj);

    Transform t;

    PointLight p("LIGHt", program);
    p.getTransform().setPosition(pos);
    p.intensity = 0.75f;
    p.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    CustomCommand moveLight ([&p]() { p.getTransform().translate(Time::instance().deltaTime() * glm::vec3(0.0, 1.0, 0.0)); });
    in.assignCommandToKeyEvent(std::pair(GLFW_KEY_UP, KeyAction::HOLD), moveLight);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (!win.shouldClose()) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        Time::instance().update();

        in.fillCommandQueue(cmds);
        for (auto cmd : cmds) {
            cmd.get().execute();
        }

        player.update();

        auto c = player.getComponent<Camera>()->get();
        program.setUniformValue("view", c.getViewMat());

        maya.getTransform().rotate(0.5f * Time::instance().deltaTime(), glm::vec3(0.0f, 1.0f, 0.0f));

        p.update();

        drawer.draw(maya, renderer, program);

        win.update();

        cmds.clear();
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}