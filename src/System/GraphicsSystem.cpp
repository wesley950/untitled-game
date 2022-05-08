//
// Created by wesley on 03/05/22.
//

#include "GraphicsSystem.hpp"
#include "Components.hpp"
#include "Components_Player.hpp"

#include "Core/MainLoop.hpp"
#include "Server/PhysicsServer.hpp"
#include "Server/RenderingServer.hpp"

void GraphicsSystem::init() {

}

void GraphicsSystem::submit() {
    // Copy the transforms from the PhysicsSystem to the Transform components
    MainLoop::get_registry().view<TransformComponent, RigidBodyComponent>().each([] (auto entity, auto& transform_component, auto& rigid_body_component) {
        transform_component.m_Position = PhysicsServer::get_body_position(rigid_body_component.m_Body);
    });

    // Set the viewport position to the same as the player entity
    MainLoop::get_registry().view<TransformComponent, PlayerComponent>().each([] (auto entity, auto& tc, auto& pc) {
        RenderingServer::set_viewport_position(tc.m_Position);
    });

    // Tick the sprite animators
    MainLoop::get_registry().view<SpriteComponent, SpriteAnimatorComponent>().each([] (auto entity, auto& sc, auto& sac) {
        if (sac.m_CurrentVariant) {
            sac.m_AnimTime += sac.m_CurrentVariant->m_AdvanceSpeed * MainLoop::get_delta_time();

            if (sac.m_AnimTime >= (float)sac.m_CurrentVariant->m_Frames.size()) {
                sac.m_AnimTime = 0.0f;
            }

            int32_t current_frame_idx = (int32_t) sac.m_AnimTime;
            auto& current_frame = sac.m_CurrentVariant->m_Frames.at(current_frame_idx);
            float tile_width = 1.0f / sac.m_CurrentVariant->m_HorizontalFrames;
            float tile_height = 1.0f / sac.m_CurrentVariant->m_VerticalFrames;

            sc.m_UV1.x = tile_width * current_frame.x;
            sc.m_UV2.x = tile_width * (current_frame.x + 1);
            sc.m_UV1.y = tile_height * current_frame.y;
            sc.m_UV2.y = tile_height * (current_frame.y + 1);
        }
    });

    // Y-Sort sprites
    auto renderable_sprites = MainLoop::get_registry().group<TransformComponent, SpriteComponent>();
    renderable_sprites.sort<TransformComponent>([] (const auto& left, const auto& right) {
        return left.m_Position.y < right.m_Position.y;
    });

    // Submit sprites
    renderable_sprites.each([] (auto entity, auto& transform_component, auto& sprite_component) {
        RenderingServer::submit_quad(transform_component.get_transformation(),
                                     sprite_component.m_Size, sprite_component.m_Center, sprite_component.m_Color,
                                     sprite_component.m_UV1, sprite_component.m_UV2, (sprite_component.m_Texture) ? sprite_component.m_Texture->get_handle() : 0);
    });
}
