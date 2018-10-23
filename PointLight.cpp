//
// Created by kyle on 8/27/18.
//

#include "PointLight.h"
#include <glm/gtx/string_cast.hpp>

PointLight::PointLight(GameObjectID id, ShaderProgram& shader)
:GameObject(std::move(id)),
m_shaderProgram(shader)
{}

void PointLight::update() {
    GameObject::update();

    m_shaderProgram.setUniformValue("lightPosition", getTransform().position());
    m_shaderProgram.setUniformValue("lightColor", lightColor);
    m_shaderProgram.setUniformValue("lightIntensity", intensity);
}
