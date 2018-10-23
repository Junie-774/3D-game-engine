//
// Created by kyle on 8/1/18.
//

#include "GLTexture.h"
#include <iostream>

GLTexture::GLTexture() {
    glGenTextures(1, &m_id);
}

GLTexture::GLTexture(GLTexture&& other) noexcept
        : m_id(other.m_id),
          m_type(other.m_type) {
    other.m_id = 0;
}

GLTexture& GLTexture::operator=(GLTexture&& other) noexcept {
    m_id = other.m_id;
    m_type = other.m_type;
    other.m_id = 0;

    return *this;
}

GLTexture::GLTexture(const GLTexture::TextureOptions& options, unsigned char* imgData, GLenum dataFormat)
        : GLTexture() {
    generate(options, imgData, dataFormat);
}

GLTexture::TextureOptions::TextureOptions()
        : dimensions{},
          minFilter(GL_LINEAR), magFilter(GL_LINEAR),
          wrapS(GL_REPEAT), wrapT(GL_REPEAT),
          format(GL_RGB) {}

GLTexture::TextureOptions::TextureOptions(
        const TexDimensions dimensions,
        const GLuint minFilter, const GLuint magFilter,
        const GLuint wrapS, const GLuint wrapT,
        const GLuint format)

        : dimensions(dimensions),
          minFilter(minFilter), magFilter(magFilter),
          wrapS(wrapS), wrapT(wrapT),
          format(format) {}

std::string GLTexture::texTypeToString(TextureType type) {
    switch (type) {
        case TextureType::DIFFUSE:
            return "Diffuse";
        case TextureType::SPECULAR:
            return "Specular";
        default:
            return "Unknown";
    }
}

void GLTexture::bind() const {
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void GLTexture::generate(const GLTexture::TextureOptions& options, unsigned char* imgData, GLenum dataFormat) {
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, options.dimensions.x, options.dimensions.y, 0, dataFormat,
                 GL_UNSIGNED_BYTE, imgData);
    setOptions(options);
}

void GLTexture::setOptions(const GLTexture::TextureOptions& opts) {
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, opts.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, opts.magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, opts.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, opts.wrapT);
}
