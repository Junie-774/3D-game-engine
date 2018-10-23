//
// Created by kyle on 7/20/18.
//

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc,
                             std::optional<const std::string> geometryShaderSrc)
        : m_id(glCreateProgram()) {

    auto vertexResult = compileShader(vertexShaderSrc, GL_VERTEX_SHADER);
    if (std::holds_alternative<CompileError>(vertexResult)) {

        handleError(std::get<CompileError>(vertexResult));
    }

    auto fragmentResult = compileShader(fragmentShaderSrc, GL_FRAGMENT_SHADER);
    if (std::holds_alternative<CompileError>(fragmentResult)) {

        handleError(std::get<CompileError>(fragmentResult));
    }

    std::optional<GLuint> geometryShader = std::nullopt;
    if (geometryShaderSrc) {
        auto geometryResult = compileShader(*geometryShaderSrc, GL_GEOMETRY_SHADER);
        if (std::holds_alternative<CompileError>(geometryResult)) {
            handleError(std::get<CompileError>(geometryResult));
        } else geometryShader = std::get<GLuint>(geometryResult);
    }

    if (std::holds_alternative<GLuint>(vertexResult)
        && std::holds_alternative<GLuint>(fragmentResult)) {

        auto linkErr = linkProgram(
                m_id,
                std::get<GLuint>(vertexResult),
                std::get<GLuint>(fragmentResult),
                geometryShader);
        if (linkErr);
    }

}

inline void ShaderProgram::use() const {
    glUseProgram(m_id);
}

void ShaderProgram::handleError(const CompileError err) {

    std::cerr << "Error compiling shader (Type: " << shaderTypeToString(err.type) << ")\n"
              << "Info Log:\n"
              << "--------------------------------------\n"
              << err.message << "\n";
}

void ShaderProgram::handleError(const LinkError err) {

    std::cerr << "Error linking program."
              << "Info Log:\n"
              << "----------------------\n"
              << err.message << "\n";
}

std::string ShaderProgram::shaderTypeToString(const GLint type) {
    switch (type) {
        case GL_VERTEX_SHADER:
            return "GLVertex";
        case GL_FRAGMENT_SHADER:
            return "Fragment";
        case GL_GEOMETRY_SHADER:
            return "Geometry";
        default:
            return "Unknown";
    }
}

ShaderProgram::CompileResult ShaderProgram::compileShader(const std::string& source, const GLint shaderType) {

    if (shaderType != GL_VERTEX_SHADER && shaderType != GL_FRAGMENT_SHADER && shaderType != GL_GEOMETRY_SHADER) {
        throw std::runtime_error("Error: ShaderProgram::compileShader(): Invalid shader type passed");
    }

    auto shader = glCreateShader(static_cast<GLenum>(shaderType));

    auto srcPtr = source.c_str();
    glShaderSource(shader, 1, &srcPtr, nullptr);
    glCompileShader(shader);

    auto err = checkCompileErrors(shader);
    if (err) return *err;

    return shader;
}

ShaderProgram::LinkResult ShaderProgram::linkProgram(const GLuint programID,
                                                     const GLuint vertexShader,
                                                     const GLuint fragmentShader,
                                                     const std::optional<GLuint> geometryShader) {
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    if (geometryShader) glAttachShader(programID, *geometryShader);

    glLinkProgram(programID);

    return checkLinkErrors(programID);

}

std::optional<ShaderProgram::CompileError> ShaderProgram::checkCompileErrors(const GLuint shader) {

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success) {
        return std::nullopt;
    }

    int logSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);

    GLint shaderType;
    glGetShaderiv(shader, GL_SHADER_TYPE, &shaderType);

    std::string infoLog;
    infoLog.resize(static_cast<decltype(infoLog)::size_type>(logSize));

    glGetShaderInfoLog(shader, logSize, nullptr, infoLog.data());

    return CompileError{shaderType, shader, infoLog};
}

std::optional<ShaderProgram::LinkError> ShaderProgram::checkLinkErrors(const GLuint programID) {

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);

    if (success) return std::nullopt;

    int logSize;
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logSize);

    std::string infoLog;
    infoLog.resize(static_cast<decltype(infoLog)::size_type>(logSize));

    glGetProgramInfoLog(programID, logSize, nullptr, infoLog.data());

    return LinkError{programID, infoLog};
}

void ShaderProgram::setUniformValue(const std::string& name, const GLint value) {
    use();
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setUniformValue(const std::string& name, const GLuint value) {
    use();
    glUniform1ui(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setUniformValue(const std::string& name, const GLfloat value) {
    use();
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setUniformValue(const std::string& name, const GLdouble value) {
    use();
    glUniform1d(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setUniformValue(const std::string& name, const GLboolean value) {
    use();
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setUniformValue(const std::string& name, const glm::vec2 value) {
    use();
    glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniformValue(const std::string& name, const glm::vec3 value) {
    use();
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniformValue(const std::string& name, const glm::vec4 value) {
    use();
    glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniformValue(const std::string& name, const glm::mat2& value) {
    use();
    glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniformValue(const std::string& name, const glm::mat3& value) {
    use();
    glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniformValue(const std::string& name, const glm::mat4& value) {
    use();
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
