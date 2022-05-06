//
// Created by wesley on 19/04/22.
//

#pragma once

#include "System/Components.hpp"

#include <memory>

#include "glm/glm/glm.hpp"
#include "entt/src/entt/entt.hpp"

struct PlayerComponent {
    enum Item {
        NONE,
        AXE,
        PICKAXE,
        HOE,
        WATER_CAN,
        FISHING_ROD,
        CARROT_SEED,
        CABBAGE_SEED
    };

    float m_MoveSpeed = 5.0f;
    glm::vec2 m_LastNonZeroDirection { 0.0f, 1.0f };

    // Animations
    std::shared_ptr<SpriteAnimatorComponent::Animation> m_IdleAnim {};
    std::shared_ptr<SpriteAnimatorComponent::Animation> m_WalkAnim {};

    // Interactions
    entt::handle m_InteractionHitIndicator {};
    Item m_CurrentItem = Item::NONE;
    float m_CurrentActionRemainingTime = 0.0f;
    float m_AxeSwingDuration = 0.0f;
    float m_PickaxeSwingDuration = 0.0f;
    float m_HoeSwingDuration = 0.0f;
    float m_WateringDuration = 0.0f;
    float m_FishingRodSwingDuration = 0.0f;
    float m_PlantDuration = 0.0f;
};
