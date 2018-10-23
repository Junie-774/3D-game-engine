//
// Created by kyle on 7/21/18.
//

#ifndef SPACEBOIS_MESHRENDERER_H
#define SPACEBOIS_MESHRENDERER_H

#include "OpenGL/GLMesh.h"
#include "ShaderProgram.h"
#include "Transform.h"

class GLMeshDrawer {
public:
    void renderMesh(const GLMesh& mesh, const Transform& transform, ShaderProgram& program) const;

};


#endif //SPACEBOIS_MESHRENDERER_H
