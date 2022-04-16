//
// Created by wesley on 16/04/22.
//

#include "GL3VertexArray.hpp"

void GL3VertexArray::bind() {
    if (m_Handle == 0)
        create();

    glBindVertexArray(m_Handle);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
}

void GL3VertexArray::set_vertices(const std::vector<Vertex> &vertices) {
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vertex) * vertices.size()), vertices.data(), GL_STATIC_DRAW);
}

void GL3VertexArray::set_indices(const std::vector<uint32_t> &indices) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(uint32_t) * indices.size()), indices.data(), GL_STATIC_DRAW);
    m_ElementCount = (int32_t)indices.size();
}

void GL3VertexArray::draw() {
    glDrawElements(GL_TRIANGLES, m_ElementCount, GL_UNSIGNED_INT, (const void*)0);
}

void GL3VertexArray::release() {
    glDeleteBuffers(1, &m_IndexBuffer);
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteVertexArrays(1, &m_Handle);

    m_IndexBuffer = m_VertexBuffer = m_Handle = 0;
    m_ElementCount = 0;
}

void GL3VertexArray::create() {
    glGenVertexArrays(1, &m_Handle);
    glGenBuffers(1, &m_VertexBuffer);
    glGenBuffers(1, &m_IndexBuffer);
}

VertexArray* create_vertex_array() {
    return new GL3VertexArray();
}
