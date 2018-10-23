//
// Created by kyle on 9/8/18.
//

#ifndef SPACEBOIS_BUFFER_H
#define SPACEBOIS_BUFFER_H

#include <cassert>
#include <iostream>
#include <type_traits>
#include <vector>
#include <GL/glew.h>

template <class T>
class GLBuffer;

template<GLenum BufferTarget>
class BufferBinding {

    static constexpr GLenum getBindingParam() noexcept {

        switch (BufferTarget) {
            case GL_ARRAY_BUFFER:
                return GL_ARRAY_BUFFER_BINDING;
            case GL_ATOMIC_COUNTER_BUFFER:
                return GL_ATOMIC_COUNTER_BUFFER_BINDING;
            case GL_COPY_READ_BUFFER:
                return GL_COPY_READ_BUFFER_BINDING;
            case GL_COPY_WRITE_BUFFER:
                return GL_COPY_WRITE_BUFFER_BINDING;
            case GL_DISPATCH_INDIRECT_BUFFER:
                return GL_DISPATCH_INDIRECT_BUFFER_BINDING;
            case GL_DRAW_INDIRECT_BUFFER:
                return GL_DRAW_INDIRECT_BUFFER_BINDING;
            case GL_ELEMENT_ARRAY_BUFFER:
                return GL_ELEMENT_ARRAY_BUFFER_BINDING;
            case GL_PIXEL_PACK_BUFFER:
                return GL_PIXEL_PACK_BUFFER_BINDING;
            case GL_PIXEL_UNPACK_BUFFER:
                return GL_PIXEL_UNPACK_BUFFER_BINDING;
            case GL_QUERY_BUFFER:
                return GL_QUERY_BUFFER_BINDING;
            case GL_SHADER_STORAGE_BUFFER:
                return GL_SHADER_STORAGE_BUFFER_BINDING;
            case GL_TEXTURE_BUFFER:
                return GL_TEXTURE_BUFFER_BINDING;
            case GL_TRANSFORM_FEEDBACK_BUFFER:
                return GL_TRANSFORM_FEEDBACK_BUFFER_BINDING;
            case GL_UNIFORM_BUFFER:
                return GL_UNIFORM_BUFFER_BINDING;

            default:
                return 0;
        }
    }

public:
    explicit BufferBinding(const GLuint handle) noexcept {
        assert(!bound);

        glBindBuffer(BufferTarget, handle);
        bound = true;
    }

    template<class T>
    explicit BufferBinding(const GLBuffer<T>& buff) noexcept
        :BufferBinding(buff.m_handle)
    {}

    ~BufferBinding() noexcept {
        glBindBuffer(BufferTarget, 0);
        bound = false;
    }

private:

    static bool bound;
};

template <GLenum BufferTarget>
bool BufferBinding<BufferTarget>::bound = false;

template<class T>
class GLBuffer {
public:
    GLBuffer() = default;

    GLBuffer (const GLBuffer<T>& other) = delete;

    GLBuffer (GLBuffer<T>&& other) noexcept
            : m_size(other.m_size),
              m_handle(other.m_handle) {

        other.m_size = 0;
        other.m_handle = 0;
    }

    explicit GLBuffer (const std::vector<T>& source, GLenum usage = GL_STATIC_DRAW) {

        assignData(source, usage);
    }

    ~GLBuffer() {
        glDeleteBuffers(1, &m_handle);
    }

    GLBuffer& operator=(const GLBuffer<T>& other) noexcept {

        if (this != &other) {
            assignData(other);
        }

        return *this;
    }

    GLBuffer& operator=(GLBuffer<T>&& other) noexcept {
        m_size = other.m_size;
        m_handle = other.m_handle;

        other.m_size = 0;
        other.m_handle = 0;

        return *this;
    }

    void assignData(const std::vector<T> source, GLenum usage = GL_STATIC_DRAW) noexcept {
        if (!m_handle) {
            glGenBuffers(1, &m_handle);
        }

        m_size = static_cast<GLsizei>(sizeof(typename decltype(source)::value_type) * source.size());
        BufferBinding<GL_COPY_WRITE_BUFFER> bufferBinding(m_handle);
        glBufferData(GL_COPY_WRITE_BUFFER,
                     m_size,
                     source.data(),
                     usage);
    }

    void assignData(const GLBuffer<T>& source) noexcept {

        if (!m_handle) {
            glGenBuffers(1, &m_handle);
        }

        m_size = source.m_size;
        glNamedBufferData(m_handle, m_size, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, m_size);
    };

    std::vector<T> getData() const {
        std::vector<T> ret;
        ret.reserve(m_size / sizeof(T));
        glGetNamedBufferSubData(m_handle, 0, m_size, ret.data());
    }

private:
    template <GLenum>
    friend class BufferBinding;

    GLuint m_handle = 0;

    GLsizei m_size = 0;

};


#endif //SPACEBOIS_BUFFER_H
