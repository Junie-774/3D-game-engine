//
// Created by kyle on 9/17/18.
//

#ifndef SPACEBOIS_MESH_H
#define SPACEBOIS_MESH_H

#include <vector>
#include "Face.h"
#include "Vertex.h"

struct Mesh {

    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;
};


#endif //SPACEBOIS_MESH_H
