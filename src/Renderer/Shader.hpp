//
// Created by wesley on 16/04/22.
//

#ifndef UNTITLED_SHADER_HPP
#define UNTITLED_SHADER_HPP

#include <glm/mat4x4.hpp>

class Shader {
public:
    virtual ~Shader() = default;

    virtual void bind() = 0;
    virtual void set_uniforms(const glm::mat4& projectionView) = 0;
    virtual void release() = 0;

};

Shader* create_shader();

#endif //UNTITLED_SHADER_HPP
