//
// Created by kyle on 7/21/18.
//

#ifndef SPACEBOIS_MESH_H
#define SPACEBOIS_MESH_H

#include <vector>
#include <GL/glew.h>
#include "OpenGL/GLBuffer.h"
#include "Component/Component.h"
#include "Material.h"
#include "GLTexture.h"
#include "GLVertex.h"


class GLMesh {
public:
    GLMesh() = default;

    GLMesh(const GLMesh& other) = delete;
    GLMesh& operator= (const GLMesh& other) = delete;

    GLMesh(GLMesh&& other) noexcept;
    GLMesh& operator= (GLMesh&& other) noexcept;

    GLMesh(const std::vector<GLVertex>& vertices, const std::vector<GLuint>& indices, Material mat = Material{});

    ~GLMesh();

    GLuint getVAO() const;

private:
    friend class GLMeshDrawer;

    enum {
        ATTRIBLOC_POSITION = 0,
        ATTRIBLOC_NORMAL = 1,
        ATTRIBLOC_TEXCOORD = 2
    };


    GLuint m_vertexArray =
            [t = this]() {
                if (!t) std::cout << "WTF\n";
                std::remove_const<decltype(m_vertexArray)>::type vao;
                glGenVertexArrays(1, &vao);
                return vao;
            }();


    GLBuffer<GLVertex> m_vertexBuffer;
    GLBuffer<GLuint> m_elementBuffer;

    GLuint m_numIndices = 0;
    Material m_material;
};

typedef std::reference_wrapper<GLMesh> MeshRef;
typedef std::reference_wrapper<const GLMesh> ConstMeshRef;

bool operator < (const GLMesh& lhs, const GLMesh& rhs);


#endif //SPACEBOIS_MESH_H
