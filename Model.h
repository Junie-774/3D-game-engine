//
// Created by kyle on 9/8/18.
//

#ifndef SPACEBOIS_MODEL_H
#define SPACEBOIS_MODEL_H

#include "OpenGL/GLMesh.h"

class Model {
public:
    Model() noexcept = default;

    Model(const Model& other) = default;
    Model& operator=(const Model& other) = default;

    Model(Model&& other) = default;
    Model& operator=(Model&& other) = default;

    explicit Model(std::vector<GLMesh> meshes) noexcept;

    std::vector<GLMesh>& meshes();
    const std::vector<GLMesh>& meshes() const;
private:
    std::vector<GLMesh> m_meshes = {};
};



#endif //SPACEBOIS_MODEL_H
