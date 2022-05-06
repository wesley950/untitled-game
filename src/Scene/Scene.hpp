//
// Created by wesley on 15/04/22.
//

#pragma once

#include "System/Components.hpp"

#include <string>
#include <unordered_map>

#include <entt/entt.hpp>
#include <box2d/box2d.h>

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    void start();
    void update(float deltaTime);
    void render();
    void release();

    entt::handle create_basic(const std::string& tag = "Basic Actor");

    void draw_debug_windows(bool show_player_debugger);
private:

    void populate();
    void create_player();
    void update_player(float deltaTime);

    void draw_player_debug_windows();

private:
    entt::registry m_Registry {};
    entt::handle m_Player {};

    b2World* m_PhysicsWorld = nullptr;
};
