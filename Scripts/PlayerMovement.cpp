//
// Created by kyle on 8/21/18.
//

#include <iostream>
#include "Component/Camera.h"
#include <glm/gtx/string_cast.hpp>
#include "PlayerMovement.h"

PlayerMovement::PlayerMovement(GameObject& player, InputManager& inputManager)
:m_player(player),
 m_camera(player.getComponent<Camera>()->get()),
 m_inputManager(inputManager)
{

}

void PlayerMovement::start() {

}

void PlayerMovement::update() {

    glm::vec3 move(0);
    glm::vec3 front = glm::normalize(projectToXZ(m_camera.front()));
    glm::vec3 right = glm::normalize(projectToXZ(m_camera.right()));
    if (m_inputManager.isKeyDown(GLFW_KEY_W)) {
        move += front;
    }
    if (m_inputManager.isKeyDown(GLFW_KEY_A)) {
        move += -right;
    }
    if (m_inputManager.isKeyDown(GLFW_KEY_S)) {
        move += -front;
    }
    if (m_inputManager.isKeyDown(GLFW_KEY_D)) {
        move += right;
    }
    if (m_inputManager.isKeyDown(GLFW_KEY_SPACE)) {
        move += WORLD_UP;
    }
    if (m_inputManager.isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
        move += -WORLD_UP;
    }

    m_player.getTransform().translate(move * Time::instance().deltaTime());
}

void PlayerMovement::end() {}