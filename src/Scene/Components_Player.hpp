//
// Created by wesley on 19/04/22.
//

#ifndef UNTITLED_COMPONENTS_PLAYER_HPP
#define UNTITLED_COMPONENTS_PLAYER_HPP

#include <glm/glm.hpp>
#include <entt/entt.hpp>

struct PlayerComponent {
    float m_MoveSpeed = 5.0f;
    glm::vec2 m_LastNonZeroDirection { 0.0f, 1.0f };

    entt::handle m_InteractionHitIndicator {};
};

#endif //UNTITLED_COMPONENTS_PLAYER_HPP
