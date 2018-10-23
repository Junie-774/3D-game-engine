//
// Created by kyle on 8/8/18.
//

#include "Camera.h"
#include <iostream>
#include <Time.h>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera(GameObject& parent, const float yaw, const float pitch)
        : Component(parent) {
    updateVectors(getVectorFromAngles(0.0f, 0.0f));
}

glm::mat4 Camera::getViewMat() const {
    const auto pos = m_gameObj.getTransform().position();
    return glm::lookAt(pos, pos + m_frontDirection, m_upDirection);
}

constexpr float Camera::clipPitch(const float pitch) {

    return std::clamp(pitch, -MAX_PITCH, MAX_PITCH);
}

void Camera::rotateDegrees(const float deltaYaw, const float deltaPitch) {

    rotateRads(glm::radians(deltaYaw), glm::radians(deltaPitch));
}

void Camera::rotateRads(const float deltaYaw, float deltaPitch) {

    m_frontDirection = glm::rotate(m_frontDirection, deltaYaw, -WORLD_UP);
    m_frontDirection = glm::rotate(m_frontDirection, deltaPitch, m_rightDirection);
    updateVectors(m_frontDirection);
}

void Camera::lookAt(const glm::vec3 target) {

    const auto newFront = target - m_gameObj.getTransform().position();
    updateVectors(newFront);
}

glm::vec3 Camera::getVectorFromAngles(float yaw, float pitch) {

    // Standard formula for converting (r, phi, theta) to (x, y, z)
    // the elements are switched around because the Y axis is up
    return glm::vec3(
            cosf(pitch) * cosf(yaw),
            sinf(pitch),
            cosf(pitch) * sinf(yaw)
    );

}

void Camera::updateVectors(const glm::vec3 newFront) {

    m_frontDirection = glm::normalize(newFront);
    m_rightDirection = glm::normalize(glm::cross(m_frontDirection, WORLD_UP));

    // Don't need to normalize because both arguments have unit length
    m_upDirection = glm::cross(m_rightDirection, m_frontDirection);
}

