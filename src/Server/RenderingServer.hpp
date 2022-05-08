//
// Created by wesley on 03/05/22.
//

#pragma once

#include <vector>
#include <memory>

#include <cstdint>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class RenderingServer {
public:
    struct Vertex {
        glm::vec3 aPosition;
        glm::vec4 aColor;
        glm::vec2 aTextureCoordinates;
        float aTextureSlot;
    };

    // Main loop
    static void init();
    static void flush();
    static void shutdown();

    // Rendering
    static void submit_quad(const glm::mat4& transform,
                            const glm::vec2& size, const glm::vec2& center, const glm::vec4& color,
                            const glm::vec2& uv1, const glm::vec2& uv2, int32_t texture_handle);

    static void bind_texture(int32_t texture_handle, int32_t slot);

    static const glm::vec2& get_viewport_size() { return s_ViewportSize; }
    static void set_viewport_size(const glm::vec2& viewport_size) { s_ViewportSize = viewport_size; }
    static const glm::vec2& get_viewport_position() { return s_ViewportPosition; }
    static void set_viewport_position(const glm::vec2& viewport_position) { s_ViewportPosition = viewport_position; }

    static glm::vec2 screen_to_world_position(const glm::vec2& screen_pos);

    // Storage
    static int32_t create_texture();
    static void set_texture_data(int32_t texture_handle, int32_t width, int32_t height, void* pixels);
    static void destroy_texture(int32_t texture_handle);

private:
    // Rendering
    static std::vector<Vertex> s_VertexData;
    static std::vector<uint32_t> s_IndexData;
    static int32_t s_BaseIndex;
    static std::vector<int32_t> s_TextureSlots;

    static glm::vec2 s_ViewportSize;
    static glm::vec2 s_ViewportPosition;
    static float s_ViewportZoom;
    static glm::mat4 s_ProjectionViewMatrix;

    // Storage
    static int32_t s_CreatedTextures;
};
