//
// Created by kyle on 9/8/18.
//

#include "Model.h"

Model::Model(std::vector<GLMesh> meshes) noexcept
        : m_meshes(std::move(meshes)) {

}

std::vector<GLMesh>& Model::meshes() {
    return m_meshes;
}

const std::vector<GLMesh>& Model::meshes() const {
    return m_meshes;
}
