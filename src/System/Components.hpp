//
// Created by wesley on 15/04/22.
//

#pragma once

#include "Core/UUID.hpp"
#include "Renderer/Texture.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "glm/glm/vec2.hpp"
#include "glm/glm/mat4x4.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm/gtx/quaternion.hpp"

struct TagComponent {
    std::string m_Tag {};

    TagComponent(const TagComponent& other) {
        this->m_Tag = other.m_Tag;
    }

    explicit TagComponent(const std::string & tag) {
        this->m_Tag = tag;
    }
};

struct UUIDComponent {
    UUID m_UUID {};
};

struct TransformComponent {
    glm::vec2 m_Position {};
    glm::vec2 m_Scale { 1.0f, 1.0f };
    float m_Rotation = 0.0;

    [[nodiscard]] glm::mat4 get_transformation() const {
        glm::mat4 rotationMatrix = glm::toMat4(glm::quat(glm::vec3(0.0f, 0.0f, m_Rotation)));
        return glm::translate(glm::mat4(1.0f), glm::vec3(m_Position, 0.0f)) * rotationMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale, 1.0f));
    }
};

struct SpriteComponent {
    glm::vec2 m_Size { 1.0f, 1.0f };
    glm::vec2 m_Center { 0.5f, 0.5f };
    glm::vec4 m_Color { 1.0f, 1.0f, 1.0f, 1.0f };

    std::shared_ptr<Texture> m_Texture;
    glm::vec2 m_UV1 { 0.0f, 0.0f };
    glm::vec2 m_UV2 { 1.0f, 1.0f };
};

struct SpriteAnimatorComponent {
    struct Animation {
        struct Variant {
            struct Frame {
                int32_t x = 0;
                int32_t y = 0;
            };

            std::vector<Frame> m_Frames {};
            float m_AdvanceSpeed = 1.0f;
            int32_t m_HorizontalFrames = 1;
            int32_t m_VerticalFrames = 1;
        };

        std::unordered_map<std::string, std::shared_ptr<Variant>> m_Variants {};
    };

    float m_AnimTime = 0.0f;
    std::shared_ptr<Animation::Variant> m_CurrentVariant;
};

struct RigidBodyComponent {
    int32_t m_Body = -1;

    RigidBodyComponent() = default;
};

struct ShapeListComponent {
    std::vector<int32_t> m_ShapeHandles {};

    ShapeListComponent() = default;
};
