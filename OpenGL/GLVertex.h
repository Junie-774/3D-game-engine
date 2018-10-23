//
// Created by kyle on 7/21/18.
//

#ifndef SPACEBOIS_VERTEX_H
#define SPACEBOIS_VERTEX_H

#include <glm/glm.hpp>

struct GLVertex {

    // The position of the vertex
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoordinates;
};
#endif //SPACEBOIS_VERTEX_H
