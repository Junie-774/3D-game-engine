//
// Created by kyle on 7/21/18.
//

#include "GLMeshDrawer.h"

void GLMeshDrawer::renderMesh(const GLMesh& mesh, const Transform& transform, ShaderProgram& program) const {

    program.use();
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glBindVertexArray(mesh.getVAO());

    program.setUniformValue("model", transform.model());

    GLuint numTextures = 0;
    program.setUniformValue("diffuseSize", static_cast<GLuint>(mesh.m_material.diffuseMap.size()));
    for (unsigned int i = 0; i < mesh.m_material.diffuseMap.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + numTextures);
        mesh.m_material.diffuseMap[i].bind();
        program.setUniformValue("material.diffuse[" + std::to_string(i) + "]", static_cast<GLint>(numTextures));
    }

    /*
    if (mesh.m_material.specularMap) {
        glActiveTexture(GL_TEXTURE1);
        mesh.m_material.specularMap->bind();
    }
     */

    glDrawElements(GL_TRIANGLES, mesh.m_numIndices, GL_UNSIGNED_INT, nullptr);
}
