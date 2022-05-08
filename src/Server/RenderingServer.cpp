//
// Created by wesley on 03/05/22.
//

#include "RenderingServer.hpp"

// Rendering
std::vector<RenderingServer::Vertex> RenderingServer::s_VertexData {};
std::vector<uint32_t> RenderingServer::s_IndexData {};
int32_t RenderingServer::s_BaseIndex = 0;
std::vector<int32_t> RenderingServer::s_TextureSlots {};

glm::vec2 RenderingServer::s_ViewportSize { 1280.0f, 720.0f };
glm::vec2 RenderingServer::s_ViewportPosition { 0.0f, 0.0f };
float RenderingServer::s_ViewportZoom = 64.0f;
glm::mat4 RenderingServer::s_ProjectionViewMatrix = glm::mat4(1.0f);

// Storage
int32_t RenderingServer::s_CreatedTextures = 0;

glm::vec2 RenderingServer::screen_to_world_position(const glm::vec2& screen_pos) {
    glm::vec2 normalized_device_coords = {
            ((screen_pos.x / s_ViewportSize.x) * 2.0f - 1.0f),
            ((1.0f - (screen_pos.y / s_ViewportSize.y)) * 2.0f - 1.0f)
    };

    glm::vec4 temp = { normalized_device_coords, 0.0f, 1.0f };
    temp = temp / s_ProjectionViewMatrix;

    return glm::vec2(temp.x, temp.y) + s_ViewportPosition;
}
