//
// Created by wesley on 15/04/22.
//

#ifndef UNTITLED_GL3SHADER_HPP
#define UNTITLED_GL3SHADER_HPP

#include "Renderer/Shader.hpp"
#include "Generated/GL3/Shaders.hpp"

#include <cstdint>

#include <glad/glad.h>

class GL3Shader : public Shader {
public:
    GL3Shader() = default;
    ~GL3Shader() override = default;

    void bind() override;
    void set_uniforms(const glm::mat4& projectionView) override;
    void release() override;

private:
    void create();
    static GLuint compile_shader(GLenum type, const char* szCode);
    static GLuint link_program(GLuint vertex_shader, GLuint fragment_shader);

private:
    GLuint m_Handle = 0;
    GLint m_ProjectionViewUniformLoc = -1;
};


#endif //UNTITLED_GL3SHADER_HPP
