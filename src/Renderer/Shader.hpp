//
// Created by wesley on 16/04/22.
//

#pragma once

#include <vector>
#include <cstdint>

#include <glm/mat4x4.hpp>

class Shader {
public:
    virtual ~Shader() = default;

    virtual void bind() = 0;
    virtual void set_uniforms(const glm::mat4& projectionView) = 0;
    virtual void set_texture_slots(const std::vector<int32_t>& slots) = 0;
    virtual void release() = 0;

};

Shader* create_shader();
