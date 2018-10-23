//
// Created by kyle on 7/21/18.
//

#include "GLMesh.h"

GLMesh::GLMesh(GLMesh&& other) noexcept
        : m_vertexArray(other.m_vertexArray),
          m_numIndices(other.m_numIndices),
          m_material(std::move(other.m_material)),
          m_vertexBuffer(std::move(other.m_vertexBuffer)),
          m_elementBuffer(std::move(other.m_elementBuffer)) {
    other.m_vertexArray = 0;
}


GLMesh& GLMesh::operator=(GLMesh&& other) noexcept {
    m_vertexArray = other.m_vertexArray;
    other.m_vertexArray = 0;

    m_numIndices = other.m_numIndices;
    other.m_numIndices = 0;

    m_material = std::move(other.m_material);
    m_vertexBuffer = std::move(other.m_vertexBuffer);
    m_elementBuffer = std::move(other.m_elementBuffer);

    return *this;

}

GLMesh::GLMesh(const std::vector<GLVertex>& vertices, const std::vector<GLuint>& indices, const Material material)
        : m_numIndices(static_cast<decltype(m_numIndices)>(indices.size())),
          m_material(material),
          m_vertexBuffer(vertices),
          m_elementBuffer(indices) {

    // Must bind the VAO before binding and filling the element buffer, because the element buffer
    // is tracked by the VAO
    glBindVertexArray(m_vertexArray);

    // Bind the buffers so that the vertex array keeps track of things.
    BufferBinding<GL_ARRAY_BUFFER> vboBinding(m_vertexBuffer);
    BufferBinding<GL_ELEMENT_ARRAY_BUFFER> eboBinding(m_elementBuffer);

    glEnableVertexAttribArray(ATTRIBLOC_POSITION);
    glVertexAttribPointer(ATTRIBLOC_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex),
                          reinterpret_cast<GLvoid*>(offsetof(GLVertex, position)));

    glEnableVertexAttribArray(ATTRIBLOC_NORMAL);
    glVertexAttribPointer(ATTRIBLOC_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex),
                          reinterpret_cast<GLvoid*>(offsetof(GLVertex, normal)));

    glEnableVertexAttribArray(ATTRIBLOC_TEXCOORD);
    glVertexAttribPointer(ATTRIBLOC_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(GLVertex),
                          reinterpret_cast<GLvoid*>(offsetof(GLVertex, textureCoordinates)));

    glBindVertexArray(0);
}

GLuint GLMesh::getVAO() const {
    return m_vertexArray;
}

GLMesh::~GLMesh() {
    glDeleteVertexArrays(1, &m_vertexArray);
}

bool operator<(const GLMesh& lhs, const GLMesh& rhs) {
    return lhs.getVAO() < rhs.getVAO();
}
