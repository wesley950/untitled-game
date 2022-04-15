//
// Created by wesley on 15/04/22.
//

#include "Renderer.hpp"

Renderer::State Renderer::s_State {};

void Renderer::init() {

}

void Renderer::shutdown() {

}

void Renderer::begin_frame() {
    s_State.verticesDrawn = 0;
    /*
     * s_State.shader.bind();
     * s_State.shader.set_uniforms();
     * s_State.vertexArray.bind();
     */
}

void Renderer::prepare(Renderer::RenderMode mode) {
    s_State.renderMode = mode;
    s_State.vertices.clear();
    s_State.indices.clear();
    s_State.baseIndex = 0;
}

void Renderer::draw_quad(const glm::mat4 &transform, const glm::vec2 &size, const glm::vec2 &center,
                         const glm::vec4 &color) {
    glm::vec2 offset(
            -(size.x * center.x),
            -(size.y * center.y)
            );

    VertexArray::Vertex vertices[] = {
            {
                    offset
            },
            {
                    offset + glm::vec2(size.x, 0.0f)
            },
            {
                offset + size
            },
            {
                offset + glm::vec2(0.0f, size.y)
            }
    };

    for (auto& vertex : vertices) {
        glm::vec4 temp = glm::vec4(vertex.aPosition, 0, 1) * transform;
        vertex.aPosition.x = temp.x;
        vertex.aPosition.y = temp.y;
        s_State.vertices.push_back(vertex);
    }

    s_State.indices.push_back(s_State.baseIndex + 0);
    s_State.indices.push_back(s_State.baseIndex + 1);
    s_State.indices.push_back(s_State.baseIndex + 2);
    s_State.indices.push_back(s_State.baseIndex + 0);
    s_State.indices.push_back(s_State.baseIndex + 2);
    s_State.indices.push_back(s_State.baseIndex + 3);

    s_State.baseIndex += 4;
    s_State.verticesDrawn += 6;
}

void Renderer::present() {
    /*
     * s_State.vertexArray.set_vertices(s_State.vertices);
     * s_State.vertexArray.set_indices(s_State.indices);
     * s_State.vertexArray.draw();
     */
}
