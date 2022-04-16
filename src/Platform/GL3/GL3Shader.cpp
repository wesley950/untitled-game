//
// Created by wesley on 15/04/22.
//

#include "GL3Shader.hpp"
#include "Renderer/VertexArray.hpp"

#include <glm/gtc/type_ptr.hpp>

void GL3Shader::bind() {
    if (m_Handle == 0)
        create();

    glUseProgram(m_Handle);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexArray::Vertex), (const void*) offsetof(VertexArray::Vertex, aPosition));

    // Color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexArray::Vertex), (const void*) offsetof(VertexArray::Vertex, aColor));
}

void GL3Shader::set_uniforms(const glm::mat4& projectionView) {
    glUniformMatrix4fv(m_ProjectionViewUniformLoc, 1, GL_FALSE, glm::value_ptr(projectionView));
}

void GL3Shader::release() {
    glDeleteProgram(m_Handle);
    m_Handle = 0;
    m_ProjectionViewUniformLoc = -1;
}

void GL3Shader::create() {
    GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, VERTEX_SHADER_CODE);
    GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_CODE);
    m_Handle = link_program(vertex_shader, fragment_shader);

    m_ProjectionViewUniformLoc = glGetUniformLocation(m_Handle, "uProjectionView");
}

GLuint GL3Shader::compile_shader(GLenum type, const char *szCode) {
    GLuint shader = glCreateShader(type);
    GLint result = 0;

    glShaderSource(shader, 1, &szCode, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if (result == 0) {
        char infoLog[256];
        glGetShaderInfoLog(shader, 256, nullptr, infoLog);
        // TODO: error log this using spd-log
    }

    return shader;
}

GLuint GL3Shader::link_program(GLuint vertex_shader, GLuint fragment_shader) {
    GLuint program = glCreateProgram();
    GLint result = 0;

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if (result == 0) {
        char infoLog[256];
        glGetProgramInfoLog(program, 256, nullptr, infoLog);
        // TODO: error log this using spd-log
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

Shader* create_shader() {
    return new GL3Shader();
}
