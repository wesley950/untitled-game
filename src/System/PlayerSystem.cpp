//
// Created by wesley on 03/05/22.
//

#include "PlayerSystem.hpp"
#include "SceneSystem.hpp"

#include "Components.hpp"
#include "Components_Player.hpp"

#include "Core/MainLoop.hpp"
#include "Resource/ResourceManager.hpp"
#include "Input/Input.hpp"
#include "Server/PhysicsServer.hpp"

void PlayerSystem::init() {
    entt::handle player_handle = SceneSystem::create_entity();
    auto& transform_component = player_handle.get<TransformComponent>();
    auto& sprite_component = player_handle.emplace<SpriteComponent>();
    auto& player_component = player_handle.emplace<PlayerComponent>();
    auto& rigid_body_component = player_handle.emplace<RigidBodyComponent>();
    auto& shape_list_component = player_handle.emplace<ShapeListComponent>();
    auto& sprite_animator_component = player_handle.emplace<SpriteAnimatorComponent>();

    transform_component.m_Position = { 0.5f, 0.5f };

    // Setup the sprite
    sprite_component.m_Center = { 0.5f, 1.0f };
    sprite_component.m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
    sprite_component.m_Size = { 2.0f, 2.0f };
    sprite_component.m_Texture = ResourceManager::get_texture("char1");

    // Setup the animation refs
    player_component.m_IdleAnim = ResourceManager::get_sprite_animation("human/idle");
    player_component.m_WalkAnim = ResourceManager::get_sprite_animation("human/walk");
    sprite_animator_component.m_CurrentVariant = player_component.m_IdleAnim->m_Variants.at("down");

    // Setup the collision shape and rigid body
    rigid_body_component.m_Body = PhysicsServer::create_rigid_body(transform_component.m_Position, {0.5f, 0.5f}, true);
    shape_list_component.m_ShapeHandles.push_back(PhysicsServer::create_sphere_shape(rigid_body_component.m_Body, 0.5f, { 0.0f, 0.5f }));

    // Setup the Player Interaction Hit Indicator (PIHI)
    auto pihi = SceneSystem::create_entity();
    auto& pihi_sprite_component = pihi.emplace<SpriteComponent>();
    pihi_sprite_component.m_Center = { 0.5f, 1.0f };
    pihi_sprite_component.m_Color = { 1.0f, 1.0f, 1.0f, 0.65f };
    player_component.m_InteractionHitIndicator = pihi;
}

void PlayerSystem::update() {
    glm::vec2 direction { 0.0f, 0.0f };

    // Player movement
    MainLoop::get_registry().view<PlayerComponent, RigidBodyComponent>().each([&direction] (auto entity, auto& player_component, auto& rigid_body_component) {
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
            player_component.m_LastNonZeroDirection = direction;
            direction *= player_component.m_MoveSpeed;
        }

        PhysicsServer::set_body_linear_velocity(rigid_body_component.m_Body, direction);
    });

    // Player animations
    MainLoop::get_registry().view<PlayerComponent, SpriteAnimatorComponent>().each([&direction] (auto entity, auto& player_component, auto& sprite_animator_component) {
        bool walking = glm::length(direction) > 0.0f;

        if (glm::length(direction) > 0.0f) {
            if (player_component.m_LastNonZeroDirection.x > 0.0f)
                sprite_animator_component.m_CurrentVariant = player_component.m_WalkAnim->m_Variants.at("right");
            else if (player_component.m_LastNonZeroDirection.x < 0.0f)
                sprite_animator_component.m_CurrentVariant = player_component.m_WalkAnim->m_Variants.at("left");
            else {
                if (player_component.m_LastNonZeroDirection.y > 0.0f)
                    sprite_animator_component.m_CurrentVariant = player_component.m_WalkAnim->m_Variants.at("down");
                else if (player_component.m_LastNonZeroDirection.y < 0.0f)
                    sprite_animator_component.m_CurrentVariant = player_component.m_WalkAnim->m_Variants.at("up");
            }
        }
        else {
            if (player_component.m_LastNonZeroDirection.x > 0.0f)
                sprite_animator_component.m_CurrentVariant = player_component.m_IdleAnim->m_Variants.at("right");
            else if (player_component.m_LastNonZeroDirection.x < 0.0f)
                sprite_animator_component.m_CurrentVariant = player_component.m_IdleAnim->m_Variants.at("left");
            else {
                if (player_component.m_LastNonZeroDirection.y > 0.0f)
                    sprite_animator_component.m_CurrentVariant = player_component.m_IdleAnim->m_Variants.at("down");
                else if (player_component.m_LastNonZeroDirection.y < 0.0f)
                    sprite_animator_component.m_CurrentVariant = player_component.m_IdleAnim->m_Variants.at("up");
            }
        }
    });

    // PIHI position update
    MainLoop::get_registry().view<PlayerComponent>().each([] (auto entity, PlayerComponent& player_component) {
        auto pihi = player_component.m_InteractionHitIndicator;
        auto& transform_component = pihi.get<TransformComponent>();

        transform_component.m_Position = Input::mouse_world_position();
        transform_component.m_Position = glm::floor(transform_component.m_Position) + glm::vec2(0.5f, 1.0f);
    });
}
