//
// Created by kyle on 8/12/18.
//

#ifndef SPACEBOIS_PHYSICSBODY_H
#define SPACEBOIS_PHYSICSBODY_H

#include <functional>
#include <glm/glm.hpp>
#include "Component/Component.h"
#include "GameObject.h"
#include "Time.h"

class PhysicsBody : public Component {
public:
    static constexpr auto TYPE = "PhysicsBody";
    const std::string type() const override { return PhysicsBody::TYPE; }

    explicit PhysicsBody(GameObject& parent);

    void addForce(glm::vec3 force);

    float mass;
    glm::vec3 linearVelocity;

private:
    glm::vec3 linearAcceleration;
};

using PhysicsBodyRef = std::reference_wrapper<PhysicsBody>;

#endif //SPACEBOIS_PHYSICSBODY_H
