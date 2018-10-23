//
// Created by kyle on 9/8/18.
//

#include "GameObjectDrawer.h"

void GameObjectDrawer::draw(const GameObject& obj, const GLMeshDrawer& meshDrawer, ShaderProgram& program) const {

    if (!obj.model()) {
        return;
    }

    for (auto& mesh : obj.model()->meshes()) {
        meshDrawer.renderMesh(mesh, obj.getTransform(), program);
    }
}
