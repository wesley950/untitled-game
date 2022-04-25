//
// Created by wesley on 15/04/22.
//

#ifndef UNTITLED_RENDERER_HPP
#define UNTITLED_RENDERER_HPP

#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"

#include <vector>
#include <unordered_map>
#include <cstdint>

#include <glm/glm.hpp>

class Renderer {
public:
    struct State {
        int32_t verticesDrawn = 0;

        std::vector<VertexArray::Vertex> vertices {};
        std::vector<uint32_t> indices {};
        uint32_t baseIndex = 0;

        glm::mat4 projectionViewMat;
        glm::vec2 cameraPosition;
        glm::vec2 cameraZoom;
        glm::vec2 viewportSize;

        Shader* shader = nullptr;
        VertexArray* vertexArray = nullptr;
    };

    static void init();
    static void shutdown();

    static void begin_frame();
    static void prepare();
    static void draw_quad(const glm::mat4& transform, const glm::vec2& size, const glm::vec2& center, const glm::vec4& color);
    static void present();

    static void set_viewport_size(const glm::vec2& viewportSize);
    static void set_viewport_position(const glm::vec2& viewport_position);
    static glm::vec2 screen_to_world_position(const glm::vec2& screen_pos);

private:
    static void calculate_projection_view_matrix();

private:
    static State s_State;
};


#endif //UNTITLED_RENDERER_HPP
