//
// Created by kyle on 7/20/18.
//

#ifndef SPACEBOIS_SHADERPROGRAM_H
#define SPACEBOIS_SHADERPROGRAM_H

#include <iostream>
#include <optional>
#include <utility>
#include <string>
#include <variant>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
public:
    ShaderProgram(const std::string& vertexShaderSrc,
                  const std::string& fragmentShaderSrc,
                  std::optional<const std::string> geometryShaderSrc = std::nullopt);

    void use() const;

    void setUniformValue(const std::string& name, GLint value);
    void setUniformValue(const std::string& name, GLuint value);
    void setUniformValue(const std::string& name, GLfloat value);
    void setUniformValue(const std::string& name, GLdouble value);
    void setUniformValue(const std::string& name, GLboolean value);
    void setUniformValue(const std::string& name, glm::vec2 value);
    void setUniformValue(const std::string& name, glm::vec3 value);
    void setUniformValue(const std::string& name, glm::vec4 value);
    void setUniformValue(const std::string& name, const glm::mat2& value);
    void setUniformValue(const std::string& name, const glm::mat3& value);
    void setUniformValue(const std::string& name, const glm::mat4& value);

private:

    struct LinkError {
        GLuint program;
        std::string message;
    };

    struct CompileError {
        GLint type;
        GLuint shader;
        std::string message;
    };

    typedef std::variant<GLuint, CompileError> CompileResult;
    typedef std::optional<LinkError> LinkResult;

    GLuint m_id;

    void handleError(CompileError err);
    void handleError(LinkError err);

    static std::string shaderTypeToString(GLint type);

    static std::optional<CompileError> checkCompileErrors(GLuint shader);
    static std::optional<LinkError> checkLinkErrors(GLuint programID);

    CompileResult compileShader(const std::string& source, GLint shaderType);
    static LinkResult linkProgram(GLuint programID, GLuint vertexShader, GLuint fragmentShader, std::optional<GLuint> geometryShader);

};


#endif //SPACEBOIS_SHADERPROGRAM_H
