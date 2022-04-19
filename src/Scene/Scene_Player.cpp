//
// Created by wesley on 17/04/22.
//

#include "Scene.hpp"
#include "Components.hpp"
#include "Components_Player.hpp"

#include "Input/Input.hpp"

#include <glm/ext.hpp>

void Scene::create_player() {
    m_Player = create_basic("Player");
    auto &pc = m_Player.emplace<PlayerComponent>();

    {
        auto& sc = m_Player.get<SpriteComponent>();
        sc.m_Size = { 1.0f, 2.0f };
        sc.m_Center = { 0.5f, 1.0f };
        sc.m_Color = { 0.0f, 0.0f, 1.0f, 1.0f };
        auto &pbc = m_Player.emplace<PhysicsBodyComponent>();
        auto &pslc = m_Player.emplace<PhysicsShapeListComponent>();
        pslc.m_ShapeDefs = {
                { {0.5f, 0.0f}, {0.0f, -0.5f}, PhysicsShapeListComponent::ShapeType::ST_SPHERE }
        };
    }

    // Create the interaction hit indicator
    {
        auto pihi = create_basic("Player Interaction Hit Indicator");
        pc.m_InteractionHitIndicator = pihi;

        auto& sc = pihi.get<SpriteComponent>();
        sc.m_Color = { 1.0f, 0.0f, 0.0f, 0.5f };
    }
}

void Scene::update_player(float deltaTime) {
    // Player movement
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

        if (glm::length(direction) > 0.0f) {
            direction = glm::normalize(direction);
            pc.m_LastNonZeroDirection = direction;
            direction = direction * pc.m_MoveSpeed;
        }

        b2Vec2 targetVelocity(direction.x, direction.y);
        body->SetLinearVelocity(targetVelocity);
    });

    // Player Interaction Hit Indicator
    m_Registry.view<TransformComponent, PlayerComponent>().each([] (auto entity, auto& tc, auto& pc) {
       entt::handle pihi = pc.m_InteractionHitIndicator;
       auto& pihiTC = pihi.get<TransformComponent>();

       pihiTC.m_Position = tc.m_Position + pc.m_LastNonZeroDirection;
       pihiTC.m_Position = glm::floor(pihiTC.m_Position);
    });
}
