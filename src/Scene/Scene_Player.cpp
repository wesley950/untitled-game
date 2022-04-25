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
    auto& tc = m_Player.get<TransformComponent>();
    auto &pc = m_Player.emplace<PlayerComponent>();

    {
        auto& sc = m_Player.emplace<SpriteComponent>();
        sc.m_Size = { 1.0f, 2.0f };
        sc.m_Center = { 0.5f, 1.0f };
        sc.m_Color = { 0.0f, 0.0f, 1.0f, 1.0f };
        auto &pbc = m_Player.emplace<PhysicsBodyComponent>();
        auto &pslc = m_Player.emplace<PhysicsShapeListComponent>();

        create_body(pbc, tc.m_Position, false);
        add_circle_shape(pbc, pslc, 0.5f, b2Vec2(0.0f, -0.5f));
        /*
        pslc.m_ShapeDefs = {
                { {0.5f, 0.0f}, {0.0f, -0.5f}, PhysicsShapeListComponent::ShapeType::ST_SPHERE }
        };
         */
    }

    // Create the interaction hit indicator
    {
        auto pihi = create_basic("Player Interaction Hit Indicator");
        pc.m_InteractionHitIndicator = pihi;

        auto& sc = pihi.emplace<SpriteComponent>();
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

    // Player Interactions
    m_Registry.view<TransformComponent, PlayerComponent>().each([this] (auto entity, auto& tc, auto& pc) {
        // Player Interaction Hit Indicator
        entt::handle pihi = pc.m_InteractionHitIndicator;
        auto& pihiTC = pihi.get<TransformComponent>();

        pihiTC.m_Position = tc.m_Position + pc.m_LastNonZeroDirection;
        pihiTC.m_Position = glm::floor(pihiTC.m_Position);

        // Tool and item cycling
        if (Input::is_action_just_pressed(Input::ActionName::CYCLE_TOOL)) {
            switch (pc.m_CurrentTool) {
                case PlayerComponent::Tool::HAND:
                    pc.m_CurrentTool = PlayerComponent::Tool::HOE;
                    std::printf("Current tool: hoe\n");
                    break;

                case PlayerComponent::Tool::HOE:
                    pc.m_CurrentTool = PlayerComponent::Tool::WATER_CAN;
                    std::printf("Current tool: water can\n");
                    break;

                case PlayerComponent::Tool::WATER_CAN:
                    pc.m_CurrentTool = PlayerComponent::Tool::HAND;
                    std::printf("Current tool: hand\n");
                    break;
            }
        }

        if (Input::is_action_just_pressed(Input::ActionName::CYCLE_ITEM)) {
            switch (pc.m_CurrentItem) {
                case PlayerComponent::Item::NONE:
                    pc.m_CurrentItem = PlayerComponent::Item::CARROT_SEED;
                    std::printf("Current item: carrot seed\n");
                    break;

                case PlayerComponent::Item::CARROT_SEED:
                    pc.m_CurrentItem = PlayerComponent::Item::CABBAGE_SEED;
                    std::printf("Current item: cabbage seed\n");
                    break;

                case PlayerComponent::Item::CABBAGE_SEED:
                    pc.m_CurrentItem = PlayerComponent::Item::NONE;
                    std::printf("Current item: none\n");
                    break;
            }
        }

        // Where we can water
        static std::vector<glm::ivec2> s_Holes {};
        // Where there is water
        static std::vector<glm::ivec2> s_WetHoles {};
        // Where we can not sow
        static std::vector<glm::ivec2> s_Crops {};

        // Tool usage
        if (Input::is_action_just_pressed(Input::ActionName::USE)) {
            glm::ivec2 tilePosition { (int)pihiTC.m_Position.x, (int)pihiTC.m_Position.y };

            switch (pc.m_CurrentTool) {
                case PlayerComponent::Tool::HAND:
                // Item usage
                {
                    switch (pc.m_CurrentItem) {
                        case PlayerComponent::Item::NONE:
                            break;

                        case PlayerComponent::Item::CARROT_SEED:
                            // Only spawn if there is no crop there and there is a hole
                            if (std::none_of(s_Crops.begin(), s_Crops.end(), [&](const auto &item) {
                                return item == tilePosition;
                            }) && std::any_of(s_Holes.begin(), s_Holes.end(), [&](const auto &item) {
                                return item == tilePosition;
                            })) {

                                s_Crops.push_back(tilePosition);
                                // Create carrot crop entity
                                auto carrotCropEntity = create_basic("A Carrot Crop");
                                auto& cceSC = carrotCropEntity.emplace<SpriteComponent>();
                                cceSC.m_Color = { 1.0f, 1.0f, 0.0f, 1.0f };
                                auto& cceTC = carrotCropEntity.get<TransformComponent>();
                                cceTC.m_Position = pihiTC.m_Position;
                                std::printf("spawned carrot at %d, %d\n", tilePosition.x, tilePosition.y);
                            }
                            break;

                        case PlayerComponent::Item::CABBAGE_SEED:
                            // Same thing as above
                            if (std::none_of(s_Crops.begin(), s_Crops.end(), [&](const auto &item) {
                                return item == tilePosition;
                            }) && std::any_of(s_Holes.begin(), s_Holes.end(), [&](const auto &item) {
                                return item == tilePosition;
                            })) {

                                s_Crops.push_back(tilePosition);
                                // Create cabbage crop entity
                                auto cabbageCropEntity = create_basic("A Cabbage Crop");
                                auto& cceSC = cabbageCropEntity.emplace<SpriteComponent>();
                                cceSC.m_Color = { 0.15f, 1.0f, 0.0f, 1.0f };
                                auto& cceTC = cabbageCropEntity.get<TransformComponent>();
                                cceTC.m_Position = pihiTC.m_Position;
                                std::printf("spawned cabbage at %d, %d\n", tilePosition.x, tilePosition.y);
                            }
                            break;
                    }
                }
                    break;

                case PlayerComponent::Tool::HOE:
                    // Only effectively hoe the tile if there is no hoe there.
                    // REMEMBER: there is no need to check for crops or water
                    // since that means that necessarily there is a hole.
                    // TODO: play animation even if there is already a hole
                    if (std::none_of(s_Holes.begin(), s_Holes.end(), [&](const auto &item) {
                        return item == tilePosition;
                    })) {

                        s_Holes.push_back(tilePosition);
                        // Spawn "hole" entity, lol
                        auto holeEntity = create_basic("A Hole in The Ground");
                        auto& heSC = holeEntity.emplace<SpriteComponent>();
                        heSC.m_Color = { 0.9f, 0.55f, 0.4f, 1.0f };
                        auto& heTC = holeEntity.get<TransformComponent>();
                        heTC.m_Position = pihiTC.m_Position;

                        std::printf("plowed tile at %d, %d\n", tilePosition.x, tilePosition.y);
                    }

                    break;

                case PlayerComponent::Tool::WATER_CAN:
                    // Same thing, only effectively water the tile if there is a hole there.
                    // TODO: play watering animation even if there is no hole.
                    if (std::none_of(s_WetHoles.begin(), s_WetHoles.end(), [&](const auto &item) {
                        return item == tilePosition;
                    }) && std::any_of(s_Holes.begin(), s_Holes.end(), [&](const auto &item) {
                        return item == tilePosition;
                    })) {

                        s_WetHoles.push_back(tilePosition);
                        // Spawn "wet hole" entity (ÔwÔ)
                        auto wetHoleEntity = create_basic("A Hole in The Ground");
                        auto& wheSC = wetHoleEntity.emplace<SpriteComponent>();
                        wheSC.m_Color = { 0.9f, 0.25f, 0.1f, 1.0f };
                        auto& wheTC = wetHoleEntity.get<TransformComponent>();
                        wheTC.m_Position = pihiTC.m_Position;

                        std::printf("watered tile at %d, %d\n", tilePosition.x, tilePosition.y);
                    }
                    break;
            }
        }
    });
}
