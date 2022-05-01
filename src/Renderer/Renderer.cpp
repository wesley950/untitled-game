//
// Created by wesley on 15/04/22.
//

#include "Renderer.hpp"
#include "Input/Input.hpp"

#include <glm/ext.hpp>

Renderer::State Renderer::s_State{};

void Renderer::init() {
    s_State.shader = create_shader();
    s_State.vertexArray = create_vertex_array();

    s_State.viewportSize = glm::vec2(1280.0f, 720.0f);
    s_State.cameraPosition = glm::vec2(0.0f, 0.0f);
    s_State.cameraZoom = glm::vec2(64.0f, 64.0f);
    calculate_projection_view_matrix();
}

void Renderer::shutdown() {
    s_State.shader->release();
    delete s_State.shader;

    s_State.vertexArray->release();
    delete s_State.vertexArray;

    s_State = {};
}

void Renderer::begin_frame() {
    s_State.verticesDrawn = 0;
    s_State.shader->bind();
    calculate_projection_view_matrix();
    s_State.shader->set_uniforms(s_State.projectionViewMat);
    s_State.vertexArray->bind();
    s_State.m_TextureSlots.clear();
}

void Renderer::prepare() {
    s_State.vertices.clear();
    s_State.indices.clear();
    s_State.baseIndex = 0;
}

void Renderer::draw_quad(const glm::mat4 &transform, const glm::vec2 &size, const glm::vec2 &center,
                         const glm::vec4 &color, const std::shared_ptr<Texture>& texture) {
    static const int NULL_TEXTURE = 0;

    glm::vec3 offset(
            -(size.x * center.x),
            -(size.y * center.y),
            0.0f
    );

    float texture_slot_attribute = (float)NULL_TEXTURE;

    if (texture) {
        int32_t bound_slot = NULL_TEXTURE;

        // Check if the texture id is not there
        for (int i = 0;i < s_State.m_TextureSlots.size();i++) {
            // If it is, use the slot it was bound at as the vertex attribute
            if (s_State.m_TextureSlots.at(i) == texture->get_handle()) {
                bound_slot = i;
                break;
            }
        }

        // Otherwise, push it to the array and use the index of the last element,
        // then bind the texture to the slot
        if (bound_slot == NULL_TEXTURE) {
            bound_slot = s_State.m_TextureSlots.size();
            s_State.m_TextureSlots.push_back(bound_slot);
            texture->bind(bound_slot);
        }

        // Convert the thingamabob
        texture_slot_attribute = (float)bound_slot+1;
    }

    VertexArray::Vertex vertices[] = {
            {
                    offset,
                    color, { 0.0f, 1.0f }, texture_slot_attribute
            },
            {
                    offset + glm::vec3(size.x, 0.0f, 0.0f),
                    color, { 1.0f, 1.0f }, texture_slot_attribute
            },
            {
                    offset + glm::vec3(size, 0.0f),
                    color, { 1.0f, 0.0f }, texture_slot_attribute
            },
            {
                    offset + glm::vec3(0.0f, size.y, 0.0f),
                    color, { 0.0f, 0.0f }, texture_slot_attribute
            }
    };

    for (auto &vertex: vertices) {
        glm::vec4 temp = transform * glm::vec4(vertex.aPosition, 1.0f);
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
    s_State.shader->set_texture_slots(s_State.m_TextureSlots);
    s_State.vertexArray->set_vertices(s_State.vertices);
    s_State.vertexArray->set_indices(s_State.indices);
    s_State.vertexArray->draw();
}

void Renderer::set_viewport_size(const glm::vec2 &viewportSize) {
    s_State.viewportSize = viewportSize;
}

void Renderer::set_viewport_position(const glm::vec2& viewport_position) {
    s_State.cameraPosition = viewport_position;
}

glm::vec2 Renderer::screen_to_world_position(const glm::vec2& screen_pos) {
    glm::vec2 normalized_device_coords = {
            ((screen_pos.x / s_State.viewportSize.x) * 2.0f - 1.0f),
            ((1.0f - (screen_pos.y / s_State.viewportSize.y)) * 2.0f - 1.0f)
    };

    glm::vec4 temp = { normalized_device_coords, 0.0f, 1.0f };
    temp = temp / s_State.projectionViewMat;

    return glm::vec2(temp.x, temp.y) + s_State.cameraPosition;
}

void Renderer::calculate_projection_view_matrix() {
    float halfWidth = (s_State.viewportSize.x / s_State.cameraZoom.x) / 2.0f;
    float halfHeight = (s_State.viewportSize.y / s_State.cameraZoom.y) / 2.0f;

    s_State.projectionViewMat = glm::ortho(-halfWidth, halfWidth, halfHeight, -halfHeight);
    s_State.projectionViewMat = glm::translate(s_State.projectionViewMat, glm::vec3(-s_State.cameraPosition.x, -s_State.cameraPosition.y, 0.0f));
}
