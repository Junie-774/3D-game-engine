//
// Created by kyle on 9/17/18.
//

#ifndef SPACEBOIS_VERTEX_H
#define SPACEBOIS_VERTEX_H

#include <glm/glm.hpp>

using Vertex = glm::vec3;

template <class T>
Vertex* toVertex(const T& val) {
    static_assert(sizeof(T) == sizeof(Vertex), "Error in toVertex(T), size mismatch between T and Vertex");
    return dynamic_cast<Vertex*>(&val);
}


#endif //SPACEBOIS_VERTEX_H
