//
// Created by kyle on 8/12/18.
//

#include "GameObject.h"
#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(GameObject& parent)
:Component(parent)
{

}

void PhysicsBody::addForce(glm::vec3 force) {
}