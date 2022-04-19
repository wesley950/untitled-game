//
// Created by wesley on 19/04/22.
//

#ifndef UNTITLED_COMPONENTS_PLAYER_HPP
#define UNTITLED_COMPONENTS_PLAYER_HPP

#include <glm/glm.hpp>
#include <entt/entt.hpp>

struct PlayerComponent {
    enum class Tool {
        HAND, // Sow, harvest and interact
        HOE, // Tile the ground
        WATER_CAN // Water crops and the ground
    };

    enum class Item {
        NONE,
        CARROT_SEED,
        CABBAGE_SEED
    };

    float m_MoveSpeed = 5.0f;
    glm::vec2 m_LastNonZeroDirection { 0.0f, 1.0f };

    entt::handle m_InteractionHitIndicator {};
    Tool m_CurrentTool = Tool::HAND;
    Item m_CurrentItem = Item::NONE;
};

#endif //UNTITLED_COMPONENTS_PLAYER_HPP
