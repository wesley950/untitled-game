//
// Created by wesley on 16/04/22.
//

#pragma once

#include "Renderer/VertexArray.hpp"

#include <cstdint>

#include <glad/glad.h>

class GL3VertexArray : public VertexArray {
public:
    GL3VertexArray() = default;
    ~GL3VertexArray() override = default;

    void bind() override;
    void set_vertices(const std::vector<Vertex>& vertices) override;
    void set_indices(const std::vector<uint32_t>& indices) override;
    void draw() override;
    void release() override;

private:
    void create();

private:
    GLuint m_Handle = 0;
    GLuint m_VertexBuffer = 0;
    GLuint m_IndexBuffer = 0;

    int32_t m_ElementCount = 0;
};
