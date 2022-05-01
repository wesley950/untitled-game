//
// Created by wesley on 15/04/22.
//

#pragma once

#include <vector>
#include <cstdint>

#include <glm/glm.hpp>

class VertexArray {
public:
    struct Vertex {
        glm::vec3 aPosition;
        glm::vec4 aColor;
        glm::vec2 aTextureCoordinates;
        float aTextureSlot;
    };

    virtual ~VertexArray() = default;

    virtual void bind() = 0;
    virtual void set_vertices(const std::vector<Vertex>& vertices) = 0;
    virtual void set_indices(const std::vector<uint32_t>& indices) = 0;
    virtual void draw() = 0;
    virtual void release() = 0;
};

VertexArray* create_vertex_array();
