//
// Created by wesley on 15/04/22.
//

#include "Scene.hpp"
#include "Components_Player.hpp"
#include "Renderer/Renderer.hpp"

void Scene::start() {
    m_PhysicsWorld = new b2World(b2Vec2(0.0f, 0.0f));

    // Create the initial entities
    populate();
}

void Scene::update(float deltaTime) {
    // Update the systems of entities
    {
        update_player(deltaTime);
    }

    // Step the physics simulation
    {
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        m_PhysicsWorld->Step(deltaTime, velocityIterations, positionIterations);
    }

    // Copy the transforms from the physics engine, so we can render them
    {
        m_Registry.view<PhysicsBodyComponent, TransformComponent>().each([](auto entity, auto &pbc, auto &tc) {
            b2Vec2 bodyPosition = pbc.m_Handle->GetPosition();

            tc.m_Position.x = bodyPosition.x;
            tc.m_Position.y = bodyPosition.y;
            tc.m_Rotation = pbc.m_Handle->GetAngle();
        });
    }
}

void Scene::render() {
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
        // Get the group of render able entities and sort if back-to-front
        // using the transform's y position...
        auto visibleEntities = m_Registry.group<TransformComponent, SpriteComponent>();
        visibleEntities.sort<TransformComponent>([](const TransformComponent &left, const TransformComponent &right) {
            return left.m_Position.y < right.m_Position.y;
        });
        // ...Then submit them.
        visibleEntities.each([](auto entity, TransformComponent &tc, SpriteComponent &sc) {
            Renderer::draw_quad(tc.get_transformation(), sc.m_Size, sc.m_Center, sc.m_Color);
        });
    }

    Renderer::present();
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
