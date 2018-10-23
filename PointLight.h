//
// Created by kyle on 8/27/18.
//

#ifndef SPACEBOIS_POINTLIGHT_H
#define SPACEBOIS_POINTLIGHT_H

#include <glm/glm.hpp>
#include "GameObject.h"
#include "ShaderProgram.h"

class PointLight : public GameObject {
public:
    explicit PointLight(GameObjectID id, ShaderProgram& shader);

    void update() override;

    float intensity;
    glm::vec3 lightColor;

private:
    ShaderProgram& m_shaderProgram;

};


#endif //SPACEBOIS_POINTLIGHT_H
