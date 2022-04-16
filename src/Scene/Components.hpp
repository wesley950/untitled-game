//
// Created by wesley on 15/04/22.
//

#ifndef UNTITLED_COMPONENTS_HPP
#define UNTITLED_COMPONENTS_HPP

#include "Core/UUID.hpp"
#include <string>

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

struct TagComponent {
    std::string m_Tag;

    TagComponent() {
        m_Tag = "Actor";
    }

    TagComponent(const TagComponent& other) {
        this->m_Tag = other.m_Tag;
    }

    explicit TagComponent(const std::string & tag) {
        this->m_Tag = tag;
    }
};

struct UUIDComponent {
    UUID m_UUID;

    UUIDComponent() {
        m_UUID = UUID();
    }

    UUIDComponent(const UUIDComponent& other) {
        this->m_UUID = other.m_UUID;
    }
};

struct TransformComponent {
    glm::vec2 m_Position{};
    glm::vec2 m_Scale{};
    float m_Rotation;

    TransformComponent() {
        this->m_Position = { 0.0f, 0.0f };
        this->m_Scale = { 1.0f, 1.0f };
        this->m_Rotation = 0.0f;
    }

    TransformComponent(const TransformComponent& other) {
        m_Position = other.m_Position;
        m_Scale = other.m_Scale;
        m_Rotation = other.m_Rotation;
    }

    [[nodiscard]] glm::mat4 get_transformation() const {
        glm::mat4 rotationMatrix = glm::toMat4(glm::quat(glm::vec3(0.0f, 0.0f, m_Rotation)));
        return glm::translate(glm::mat4(1.0f), glm::vec3(m_Position, 0.0f)) * rotationMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale, 1.0f));
    }
};

struct SpriteComponent {
    glm::vec2 m_Size{};
    glm::vec2 m_Center{};
    glm::vec4 m_Color{};

    SpriteComponent() {
        m_Size = { 1.0f, 1.0f };
        m_Center = { 0.5f, 0.5f };
        m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
    }

    SpriteComponent(const SpriteComponent& other) {
        this->m_Size = other.m_Size;
        this->m_Center = other.m_Center;
        this->m_Color = other.m_Color;
    }
};

#endif //UNTITLED_COMPONENTS_HPP
