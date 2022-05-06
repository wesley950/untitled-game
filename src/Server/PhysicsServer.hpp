//
// Created by wesley on 06/05/22.
//

#pragma once

#include <cstdint>

#include <glm/vec2.hpp>

class PhysicsServer {
public:
    static void init();
    static void update();
    static void shutdown();

    static int32_t create_rigid_body(const glm::vec2& initial_position, const glm::vec2& half_extents, bool dynamic);
    static int32_t create_sphere_shape(int32_t body, float radius, const glm::vec2& center);

    static void set_body_linear_velocity(int32_t body, const glm::vec2& linear_velocity);

    static glm::vec2 get_body_position(int32_t body);
};
