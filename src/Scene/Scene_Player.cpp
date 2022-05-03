//
// Created by wesley on 17/04/22.
//

#include "Scene.hpp"
#include "Components.hpp"
#include "Components_Player.hpp"

#include "Input/Input.hpp"
#include "Renderer/Texture.hpp"
#include "Resource/ResourceManager.hpp"

#include <memory>

#include <glm/ext.hpp>

#include <imgui/imgui.h>

void Scene::create_player() {
    m_Player = create_basic("Player");
    auto& tc = m_Player.get<TransformComponent>();

    // Get refs to the loaded human sprite animations
    auto &pc = m_Player.emplace<PlayerComponent>();
    pc.m_IdleAnim = ResourceManager::get_sprite_animation("human/idle");
    pc.m_WalkAnim = ResourceManager::get_sprite_animation("human/walk");

    // Calculate the duration of each action
    // TODO: this

    // Configure the sprite component
    {
        auto& sc = m_Player.emplace<SpriteComponent>();
        sc.m_Size = { 2.0f, 2.0f };
        sc.m_Center = { 0.5f, 1.0f };
        sc.m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
        sc.m_Texture = std::shared_ptr<Texture>(create_texture(), [] (Texture* ptr) { delete ptr; });
        sc.m_Texture->load_from_file("data/textures/char1.png");

        // Set default animation
        auto& sac = m_Player.emplace<SpriteAnimatorComponent>();
        sac.m_CurrentVariant = pc.m_IdleAnim->m_Variants.at("down");

        // Add physics components
        auto &pbc = m_Player.emplace<PhysicsBodyComponent>();
        auto &pslc = m_Player.emplace<PhysicsShapeListComponent>();
        create_body(pbc, tc.m_Position, false);
        add_circle_shape(pbc, pslc, 0.5f, b2Vec2(0.0f, -0.5f));
    }

    // Create the interaction hit indicator
    {
        auto pihi = create_basic("Player Interaction Hit Indicator");
        pc.m_InteractionHitIndicator = pihi;

        auto& sc = pihi.emplace<SpriteComponent>();
        sc.m_Color = { 1.0f, 1.0f, 1.0f, 0.5f };
    }
}

void Scene::update_player(float deltaTime) {
    glm::vec2 direction { 0.0f, 0.0f };

    // Player movement
    m_Registry.view<PlayerComponent, PhysicsBodyComponent>().each([&direction] (auto entity, auto& pc, auto& pbc) {
        b2Body* body = pbc.m_Handle;

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

    // Player animations
    m_Registry.view<PlayerComponent, SpriteAnimatorComponent>().each([&direction] (auto entity, auto& pc, auto& sac) {
        bool walking = glm::length(direction) > 0.0f;

        if (glm::length(direction) > 0.0f) {
            if (pc.m_LastNonZeroDirection.x > 0.0f)
                sac.m_CurrentVariant = pc.m_WalkAnim->m_Variants.at("right");
            else if (pc.m_LastNonZeroDirection.x < 0.0f)
                sac.m_CurrentVariant = pc.m_WalkAnim->m_Variants.at("left");
            else {
                if (pc.m_LastNonZeroDirection.y > 0.0f)
                    sac.m_CurrentVariant = pc.m_WalkAnim->m_Variants.at("down");
                else if (pc.m_LastNonZeroDirection.y < 0.0f)
                    sac.m_CurrentVariant = pc.m_WalkAnim->m_Variants.at("up");
            }
        }
        else {
            if (pc.m_LastNonZeroDirection.x > 0.0f)
                sac.m_CurrentVariant = pc.m_IdleAnim->m_Variants.at("right");
            else if (pc.m_LastNonZeroDirection.x < 0.0f)
                sac.m_CurrentVariant = pc.m_IdleAnim->m_Variants.at("left");
            else {
                if (pc.m_LastNonZeroDirection.y > 0.0f)
                    sac.m_CurrentVariant = pc.m_IdleAnim->m_Variants.at("down");
                else if (pc.m_LastNonZeroDirection.y < 0.0f)
                    sac.m_CurrentVariant = pc.m_IdleAnim->m_Variants.at("up");
            }
        }
    });

    // Player Interactions
    m_Registry.view<TransformComponent, PlayerComponent>().each([this] (auto entity, auto& tc, auto& pc) {
        // Player Interaction Hit Indicator
        entt::handle pihi = pc.m_InteractionHitIndicator;
        auto& pihiTC = pihi.get<TransformComponent>();

        // Set the TIHI position to be the same as the mouse but "snapped"
        pihiTC.m_Position = Input::mouse_world_position();
        pihiTC.m_Position = glm::floor(pihiTC.m_Position + glm::vec2(0.5f, 0.5f));
    });
}

void Scene::draw_player_debug_windows() {
    static const char* ITEMS[] = {
            "None", "Axe", "Pickaxe", "Hoe", "Water Can", "Fishing Rod",
            "Carrot Seed", "Cabbage Seed"
    };
    static int item_current_idx = 0;
    const char* combo_preview_value = ITEMS[item_current_idx];

    if (ImGui::Begin("Player Debugger")) {
        m_Registry.view<PlayerComponent>().each([&combo_preview_value] (auto entity, auto& pc) {
            ImGui::Text("Movement");
            ImGui::DragFloat("Move Speed", &pc.m_MoveSpeed, 0.01f, 0.01f, 20.0f);
            float last_non_zero_dir_values[] = { pc.m_LastNonZeroDirection.x, pc.m_LastNonZeroDirection.y };
            ImGui::InputFloat2("Last Non 0 Direction", last_non_zero_dir_values, "%.02f");
            ImGui::Separator();

            const char* current_item_name = "None";
            ImGui::Text("Inventory");
            switch (pc.m_CurrentItem) {
                case PlayerComponent::Item::AXE:
                    current_item_name = "Axe";
                    break;

                case PlayerComponent::Item::PICKAXE:
                    current_item_name = "Pickaxe";
                    break;

                case PlayerComponent::Item::HOE:
                    current_item_name = "Hoe";
                    break;

                case PlayerComponent::Item::WATER_CAN:
                    current_item_name = "Watering Can";
                    break;

                case PlayerComponent::Item::FISHING_ROD:
                    current_item_name = "Fishing Rod";
                    break;

                case PlayerComponent::Item::CARROT_SEED:
                    current_item_name = "Carrot Seed";
                    break;

                case PlayerComponent::Item::CABBAGE_SEED:
                    current_item_name = "Cabbage Seed";
                    break;
            }
            ImGui::Text("Current Item: %s", current_item_name);
            if (ImGui::Selectable("Dequip")) pc.m_CurrentItem = PlayerComponent::Item::NONE;
            if (ImGui::Selectable("Axe")) pc.m_CurrentItem = PlayerComponent::Item::AXE;
            if (ImGui::Selectable("Pickaxe")) pc.m_CurrentItem = PlayerComponent::Item::PICKAXE;
            if (ImGui::Selectable("Hoe")) pc.m_CurrentItem = PlayerComponent::Item::HOE;
            if (ImGui::Selectable("Watering Can")) pc.m_CurrentItem = PlayerComponent::Item::WATER_CAN;
            if (ImGui::Selectable("Fishing Rod")) pc.m_CurrentItem = PlayerComponent::Item::FISHING_ROD;
            if (ImGui::Selectable("Carrot Seed")) pc.m_CurrentItem = PlayerComponent::Item::CARROT_SEED;
            if (ImGui::Selectable("Cabbage Seed")) pc.m_CurrentItem = PlayerComponent::Item::CABBAGE_SEED;
        });
    }
    ImGui::End();
}
