//
// Created by wesley on 17/04/22.
//

#include "Scene.hpp"
#include "Components.hpp"

#include "Input/Input.hpp"

void Scene::create_player() {
    m_Player = create_basic("Player");

    auto& sc = m_Player.get<SpriteComponent>();
    sc.m_Size = { 1.0f, 2.0f };
    sc.m_Center = { 0.5f, 1.0f };
    sc.m_Color = { 0.0f, 0.0f, 1.0f, 1.0f };

    auto &pbc = m_Player.emplace<PhysicsBodyComponent>();
    auto &pslc = m_Player.emplace<PhysicsShapeListComponent>();
    pslc.m_ShapeDefs = {
            { {0.5f, 0.0f}, {0.0f, -0.5f}, PhysicsShapeListComponent::ShapeType::ST_SPHERE }
    };
    auto &pc = m_Player.emplace<PlayerComponent>();
}

void Scene::update_player(float deltaTime) {
    m_Registry.view<PlayerComponent, PhysicsBodyComponent>().each([] (auto entity, auto& pc, auto& pbc) {
        b2Body* body = pbc.m_Handle;
        glm::vec2 direction { 0.0f, 0.0f };

        if (Input::is_action_pressed(Input::ActionName::MOVE_UP))
            direction.y -= 1.0f;
        if (Input::is_action_pressed(Input::ActionName::MOVE_DOWN))
            direction.y += 1.0f;
        if (Input::is_action_pressed(Input::ActionName::MOVE_LEFT))
            direction.x -= 1.0f;
        if (Input::is_action_pressed(Input::ActionName::MOVE_RIGHT))
            direction.x += 1.0f;

        if (glm::length(direction) > 0.0f)
            direction = glm::normalize(direction) * pc.m_MoveSpeed;
        b2Vec2 targetVelocity(direction.x, direction.y);
        body->SetLinearVelocity(targetVelocity);
    });
}
