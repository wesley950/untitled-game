//
// Created by wesley on 15/04/22.
//

#include "Scene.hpp"
#include "System/Components_Player.hpp"

#include "Core/Profiler.hpp"
#include "Renderer/Renderer.hpp"

void Scene::start() {
    m_PhysicsWorld = new b2World(b2Vec2(0.0f, 0.0f));

    // Create the initial entities
    populate();
}

void Scene::update(float deltaTime) {
    PROFILER_SCOPE("Scene::update");

    // Update the systems of entities
    {
        update_player(deltaTime);
    }

    // Tick the sprite animators
    m_Registry.view<SpriteComponent, SpriteAnimatorComponent>().each([&deltaTime] (auto entity, auto& sc, auto& sac) {
        if (sac.m_CurrentVariant) {
            sac.m_AnimTime += sac.m_CurrentVariant->m_AdvanceSpeed * deltaTime;

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

    // Step the physics simulation
    {
        PROFILER_SCOPE("Scene::update Physics Simulation");
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        m_PhysicsWorld->Step(deltaTime, velocityIterations, positionIterations);
    }

    // Copy the transforms from the physics engine, so we can render them
    {
        PROFILER_SCOPE("Scene::update Copy Transforms from Box2D");

        m_Registry.view<PhysicsBodyComponent, TransformComponent>().each([](auto entity, auto &pbc, auto &tc) {
            b2Vec2 bodyPosition = pbc.m_Handle->GetPosition();

            tc.m_Position.x = bodyPosition.x;
            tc.m_Position.y = bodyPosition.y;
            tc.m_Rotation = pbc.m_Handle->GetAngle();
        });
    }
}

void Scene::render() {
    PROFILER_SCOPE("Scene::render");

    // Set the renderer view position
    {
        m_Registry.view<TransformComponent, PlayerComponent>().each([] (auto entity, auto& tc, auto& pc) {
            Renderer::set_viewport_position(tc.m_Position);
        });
    }

    Renderer::begin_frame();
    Renderer::prepare();

    // Render the sprites
    {
        auto visibleEntities = m_Registry.group<TransformComponent, SpriteComponent>();
        {
            PROFILER_SCOPE("Scene::render Y-Sort Sprites");
            // Get the group of render able entities and sort if back-to-front
            // using the transform's y position...
            visibleEntities.sort<TransformComponent>([](const TransformComponent &left, const TransformComponent &right) {
                return left.m_Position.y < right.m_Position.y;
            });
        }

        {
            PROFILER_SCOPE("Scene::render Submit Sprites");
            // ...Then submit them.
            visibleEntities.each([](auto entity, TransformComponent &tc, SpriteComponent &sc) {
                Renderer::draw_quad(tc.get_transformation(), sc.m_Size, sc.m_Center, sc.m_Color, sc.m_Texture, sc.m_UV1,
                                    sc.m_UV2);
            });
        }
    }

    Renderer::present();
}

void Scene::draw_debug_windows(bool show_player_debugger) {
    if (show_player_debugger)
        draw_player_debug_windows();
}

void Scene::release() {
    delete m_PhysicsWorld;
    m_PhysicsWorld = nullptr;
}

entt::handle Scene::create_basic(const std::string &tag) {
    auto basic = entt::handle(m_Registry, m_Registry.create());
    basic.emplace<TagComponent>(tag);
    basic.emplace<UUIDComponent>();
    basic.emplace<TransformComponent>();
    return basic;
}

void Scene::populate() {
    create_player();
}

void Scene::create_body(PhysicsBodyComponent &physicsBody, const glm::vec2& initialPosition, bool fixedPosition) {
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = (fixedPosition)? b2_staticBody : b2_dynamicBody;
    bodyDef.position.Set(initialPosition.x, initialPosition.y);
    b2Body* body = m_PhysicsWorld->CreateBody(&bodyDef);
    physicsBody.m_Handle = body;
}

void Scene::add_box_shape(PhysicsBodyComponent& physicsBody, PhysicsShapeListComponent &shapeList, const b2Vec2 &halfExtents, const b2Vec2 &center) {
    bool fixedPosition = physicsBody.m_Handle->GetType() == b2_staticBody;
    b2PolygonShape shape;
    shape.SetAsBox(halfExtents.x, halfExtents.y, center, 0.0f);
    b2Fixture* fixture;
    if (fixedPosition) {
        fixture = physicsBody.m_Handle->CreateFixture(&shape, 0.0f);
    }
    else {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixture = physicsBody.m_Handle->CreateFixture(&fixtureDef);
    }
    shapeList.m_ShapeHandles.push_back(fixture);
}

void Scene::add_circle_shape(PhysicsBodyComponent& physicsBody, PhysicsShapeListComponent &shapeList, float radius, const b2Vec2 &center) {
    bool fixedPosition = physicsBody.m_Handle->GetType() == b2_staticBody;
    b2CircleShape shape;
    shape.m_p = center;
    shape.m_radius = radius;
    b2Fixture* fixture;
    if (fixedPosition) {
        fixture = physicsBody.m_Handle->CreateFixture(&shape, 0.0f);
    }
    else {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixture = physicsBody.m_Handle->CreateFixture(&fixtureDef);
    }
    shapeList.m_ShapeHandles.push_back(fixture);
}
