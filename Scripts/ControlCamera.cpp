//
// Created by kyle on 8/22/18.
//

#include "ControlCamera.h"
#include "Time.h"
#include <glm/gtx/string_cast.hpp>

ControlCamera::ControlCamera(Camera& camera, InputManager& inputManager)
:m_camera(camera),
 m_inputManager(inputManager)
{
    m_lastCursorPos = m_inputManager.getCursorPos();
}

void ControlCamera::update() {
    auto cursorPos = m_inputManager.getCursorPos();
    auto deltaCursorPos = cursorPos - m_lastCursorPos;
    m_lastCursorPos = cursorPos;

    float lookScaling = lookSpeed * Time::instance().deltaTime();
    float deltaYaw = deltaCursorPos.x * lookScaling;
    float deltaPitch = deltaCursorPos.y * lookScaling;

    m_camera.rotateRads(deltaYaw, deltaPitch);
}
