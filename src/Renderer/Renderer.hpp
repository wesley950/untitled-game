//
// Created by wesley on 15/04/22.
//

#ifndef UNTITLED_RENDERER_HPP
#define UNTITLED_RENDERER_HPP

#include "VertexArray.hpp"

#include <vector>
#include <cstdint>

#include <glm/glm.hpp>

class Renderer {
public:
    enum RenderMode {
        NONE,
        Y_SORTED_SPRITES,
        TILE_MAP
    };

    struct State {
        RenderMode renderMode = NONE;
        int32_t verticesDrawn = 0;

        std::vector<VertexArray::Vertex> vertices {};
        std::vector<uint32_t> indices {};
        uint32_t baseIndex = 0;
    };

    static void init();
    static void shutdown();

    static void begin_frame();
    static void prepare(RenderMode mode);
    static void draw_quad(const glm::mat4& transform, const glm::vec2& size, const glm::vec2& center, const glm::vec4& color);
    static void present();

private:
    static State s_State;
};


#endif //UNTITLED_RENDERER_HPP
