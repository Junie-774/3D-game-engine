//
// Created by kyle on 8/1/18.
//

#ifndef SPACEBOIS_TEXTURE_H
#define SPACEBOIS_TEXTURE_H

#include <memory>
#include <GL/gl.h>
#include <glm/glm.hpp>

enum class TextureType {
    DIFFUSE,
    SPECULAR
};

/**
 * @brief Wrapper around an OpenGL Texture
 */
class GLTexture {
public:

    typedef glm::uvec2 TexDimensions;

    static std::string texTypeToString(TextureType type);

    struct TextureOptions {

        TextureOptions();
        TextureOptions(TexDimensions dimensions,
                       GLuint minFilter, GLuint magFilter,
                       GLuint wrapS, GLuint wrapT,
                       GLuint format);

        // Dimensions of texture
        TexDimensions dimensions;

        GLuint minFilter; // How to scale up the texture
        GLuint magFilter; // How to scale down the texture

        // What to do on wrapping
        GLuint wrapS;
        GLuint wrapT;

        // Format of the image
        GLuint format;
    };


    GLTexture(const GLTexture&) = default;
    GLTexture& operator= (const GLTexture&) = default;

    GLTexture(GLTexture&& other) noexcept;
    GLTexture& operator= (GLTexture&& other) noexcept;
    GLTexture(const TextureOptions& options, unsigned char* imgData, GLenum dataFormat);

    constexpr GLuint id() const { return m_id; }
    void bind() const;

    void generate(const TextureOptions& options, unsigned char* imgData, GLenum dataFormat);
    void setOptions(const TextureOptions& opts);

    constexpr TextureType type() const { return m_type; }

private:
    GLTexture();

    GLuint m_id;
    TextureType m_type;
};

typedef std::reference_wrapper<GLTexture> TextureRef;
typedef std::reference_wrapper<const GLTexture> ConstTextureRef;


#endif //SPACEBOIS_TEXTURE_H
