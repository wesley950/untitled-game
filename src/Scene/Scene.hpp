//
// Created by wesley on 15/04/22.
//

#ifndef UNTITLED_SCENE_HPP
#define UNTITLED_SCENE_HPP

#include <string>

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

private:
    void populate();

    void create_player();
    void update_player(float deltaTime);

private:
    entt::registry m_Registry {};
    entt::handle m_Player {};

    b2World* m_PhysicsWorld = nullptr;
};


#endif //UNTITLED_SCENE_HPP
