#include "Transform.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

Transform::Transform(const glm::vec3 initPos, glm::vec3 initScale)
    : m_position(initPos),
      m_scale(initScale),
      m_orientation(glm::quat_identity<float, glm::highp>())
{
}

glm::vec3 Transform::position() const {
   return m_position;
}

glm::vec3 Transform::rotation() const {
    return glm::eulerAngles(m_orientation);
}

glm::vec3 Transform::scale() const {
    return m_scale;
}

void Transform::setPosition(const glm::vec3 newPos) {
    m_position = newPos;
}

void Transform::setRotation(float newAngle, glm::vec3 newAxis) {
    m_orientation = glm::quat(newAngle * glm::normalize(newAxis));
}

void Transform::setScale(const glm::vec3 newScale) {
    m_scale = newScale;
}

void Transform::translate(const glm::vec3 deltaPos) {
    setPosition(m_position + deltaPos);
}

void Transform::rotate(const float angle, const glm::vec3 axis) {
    m_orientation *= glm::quat(angle * glm::normalize(axis));
}

void Transform::scale(const glm::vec3 deltaScale) {
    setScale(m_scale + deltaScale);
}

glm::mat4 Transform::model() const {
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_position);
    model *= glm::toMat4(m_orientation);
    model *= glm::scale(m_scale);
    return model;
}

