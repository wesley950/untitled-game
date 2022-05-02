//
// Created by wesley on 15/04/22.
//

#include "GL3Shader.hpp"
#include "Renderer/VertexArray.hpp"

#include <string>
#include <cstdio>

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

    // Texture Coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexArray::Vertex), (const void*) offsetof(VertexArray::Vertex, aTextureCoordinates));

    // Texture Slot
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(VertexArray::Vertex), (const void*) offsetof(VertexArray::Vertex, aTextureSlot));
}

void GL3Shader::set_uniforms(const glm::mat4& projectionView) {
    glUniformMatrix4fv(m_ProjectionViewUniformLoc, 1, GL_FALSE, glm::value_ptr(projectionView));
}

void GL3Shader::set_texture_slots(const std::vector<int32_t>& slots) {
    for (int i = 0;i < slots.size();i++) {
        std::string uniform_name = std::string("uTextureBindings") + std::to_string(i) + std::string("");
        GLint uniform_location = glGetUniformLocation(m_Handle, uniform_name.c_str());
        int32_t value = slots.at(i);
        glUniform1i(uniform_location, value);
    }
}

void GL3Shader::release() {
    glDeleteProgram(m_Handle);
    m_Handle = 0;
    m_ProjectionViewUniformLoc = -1;
}

void GL3Shader::create() {
    GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, R"(
        #version 330 core

        layout (location = 0) in vec3   aPosition;
        layout (location = 1) in vec4   aColor;
        layout (location = 2) in vec2   aTextureCoordinates;
        layout (location = 3) in float  aTextureSlot;

        out vec4    vColor;
        out vec2    vTextureCoordinates;
        out float   vTextureSlot;

        uniform mat4 uProjectionView;

        void main() {
            gl_Position = uProjectionView * vec4(aPosition, 1);

            vColor = aColor;
            vTextureCoordinates = aTextureCoordinates;
            vTextureSlot = aTextureSlot;
        }
    )");
    GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, R"(
        #version 330 core

        uniform sampler2D uTextureBindings0;
        uniform sampler2D uTextureBindings1;
        uniform sampler2D uTextureBindings2;
        uniform sampler2D uTextureBindings3;
        uniform sampler2D uTextureBindings4;
        uniform sampler2D uTextureBindings5;
        uniform sampler2D uTextureBindings6;
        uniform sampler2D uTextureBindings7;
        uniform sampler2D uTextureBindings8;
        uniform sampler2D uTextureBindings9;
        uniform sampler2D uTextureBindings10;
        uniform sampler2D uTextureBindings11;
        uniform sampler2D uTextureBindings12;
        uniform sampler2D uTextureBindings13;
        uniform sampler2D uTextureBindings14;
        uniform sampler2D uTextureBindings15;
        uniform sampler2D uTextureBindings16;
        uniform sampler2D uTextureBindings17;
        uniform sampler2D uTextureBindings18;
        uniform sampler2D uTextureBindings19;
        uniform sampler2D uTextureBindings20;
        uniform sampler2D uTextureBindings21;
        uniform sampler2D uTextureBindings22;
        uniform sampler2D uTextureBindings23;
        uniform sampler2D uTextureBindings24;
        uniform sampler2D uTextureBindings25;
        uniform sampler2D uTextureBindings26;
        uniform sampler2D uTextureBindings27;
        uniform sampler2D uTextureBindings28;
        uniform sampler2D uTextureBindings29;
        uniform sampler2D uTextureBindings30;
        uniform sampler2D uTextureBindings31;

        in vec4     vColor;
        in vec2     vTextureCoordinates;
        in float    vTextureSlot;

        out vec4 oColor;

        void main() {
            oColor = vColor;

            int texture_slot = int(vTextureSlot);
            switch (texture_slot) {
                case 1:
                oColor *= texture(uTextureBindings0, vTextureCoordinates);
                break;

                case 2:
                oColor *= texture(uTextureBindings1, vTextureCoordinates);
                break;

                case 3:
                oColor *= texture(uTextureBindings2, vTextureCoordinates);
                break;

                case 4:
                oColor *= texture(uTextureBindings3, vTextureCoordinates);
                break;

                case 5:
                oColor *= texture(uTextureBindings4, vTextureCoordinates);
                break;

                case 6:
                oColor *= texture(uTextureBindings5, vTextureCoordinates);
                break;

                case 7:
                oColor *= texture(uTextureBindings6, vTextureCoordinates);
                break;

                case 8:
                oColor *= texture(uTextureBindings7, vTextureCoordinates);
                break;

                case 9:
                oColor *= texture(uTextureBindings8, vTextureCoordinates);
                break;

                case 10:
                oColor *= texture(uTextureBindings9, vTextureCoordinates);
                break;

                case 11:
                oColor *= texture(uTextureBindings10, vTextureCoordinates);
                break;

                case 12:
                oColor *= texture(uTextureBindings11, vTextureCoordinates);
                break;

                case 13:
                oColor *= texture(uTextureBindings12, vTextureCoordinates);
                break;

                case 14:
                oColor *= texture(uTextureBindings13, vTextureCoordinates);
                break;

                case 15:
                oColor *= texture(uTextureBindings14, vTextureCoordinates);
                break;

                case 16:
                oColor *= texture(uTextureBindings15, vTextureCoordinates);
                break;

                case 17:
                oColor *= texture(uTextureBindings16, vTextureCoordinates);
                break;

                case 18:
                oColor *= texture(uTextureBindings17, vTextureCoordinates);
                break;

                case 19:
                oColor *= texture(uTextureBindings18, vTextureCoordinates);
                break;

                case 20:
                oColor *= texture(uTextureBindings19, vTextureCoordinates);
                break;

                case 21:
                oColor *= texture(uTextureBindings20, vTextureCoordinates);
                break;

                case 22:
                oColor *= texture(uTextureBindings21, vTextureCoordinates);
                break;

                case 23:
                oColor *= texture(uTextureBindings22, vTextureCoordinates);
                break;

                case 24:
                oColor *= texture(uTextureBindings23, vTextureCoordinates);
                break;

                case 25:
                oColor *= texture(uTextureBindings24, vTextureCoordinates);
                break;

                case 26:
                oColor *= texture(uTextureBindings25, vTextureCoordinates);
                break;

                case 27:
                oColor *= texture(uTextureBindings26, vTextureCoordinates);
                break;

                case 28:
                oColor *= texture(uTextureBindings27, vTextureCoordinates);
                break;

                case 29:
                oColor *= texture(uTextureBindings28, vTextureCoordinates);
                break;

                case 30:
                oColor *= texture(uTextureBindings29, vTextureCoordinates);
                break;

                case 31:
                oColor *= texture(uTextureBindings30, vTextureCoordinates);
                break;

                case 32:
                oColor *= texture(uTextureBindings31, vTextureCoordinates);
                break;
            }
        }
    )");
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
        std::printf("%s\n", infoLog);
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
