//
// Created by wesley on 15/04/22.
//

#pragma once

#include "Components.hpp"

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

private:
    void populate();
    void create_player();
    void update_player(float deltaTime);

    void create_body(PhysicsBodyComponent& physicsBody, const glm::vec2& initialPosition, bool fixedPosition);
    static void add_box_shape(PhysicsBodyComponent& physicsBody, PhysicsShapeListComponent& shapeList, const b2Vec2& halfExtents, const b2Vec2& center = b2Vec2(0.0f, 0.0f));
    static void add_circle_shape(PhysicsBodyComponent& physicsBody, PhysicsShapeListComponent& shapeList, float radius, const b2Vec2& center = b2Vec2(0.0f, 0.0f));

private:
    entt::registry m_Registry {};
    entt::handle m_Player {};

    b2World* m_PhysicsWorld = nullptr;
};
