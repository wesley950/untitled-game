//
// Created by wesley on 06/05/22.
//

#include "Core/MainLoop.hpp"
#include "Server/PhysicsServer.hpp"

#include <box2d/box2d.h>

static b2World* s_PhysicsWorld = nullptr;
static std::unordered_map<int32_t, b2Body*> s_Bodies {};
static std::unordered_map<int32_t, b2Fixture*> s_Shapes {};

// OwO
static int32_t s_BodyCount = 0;
static int32_t s_ShapeCount = 0;

void PhysicsServer::init() {
    s_PhysicsWorld = new b2World(b2Vec2(0.0f, 0.0f));
}

void PhysicsServer::update() {
    int32 velocity_iterations = 6;
    int32 position_iterations = 2;
    s_PhysicsWorld->Step(MainLoop::get_delta_time(), velocity_iterations, position_iterations);
}

void PhysicsServer::shutdown() {
    delete s_PhysicsWorld;
    s_PhysicsWorld = nullptr;

    s_Bodies.clear();
    s_Shapes.clear();
    s_BodyCount = s_ShapeCount = 0;
}

int32_t PhysicsServer::create_rigid_body(const glm::vec2& initial_position, const glm::vec2& half_extents, bool dynamic) {
    int32_t body_id = ++s_BodyCount;
    b2BodyDef body_def;
    body_def.fixedRotation = true;
    body_def.type = (dynamic) ? b2_dynamicBody : b2_staticBody;
    body_def.position.Set(initial_position.x, initial_position.y);
    b2Body* body_ptr = s_PhysicsWorld->CreateBody(&body_def);
    s_Bodies[body_id] = body_ptr;
    return body_id;
}

int32_t PhysicsServer::create_sphere_shape(int32_t body, float radius, const glm::vec2& center) {
    int32_t shape_id = ++s_ShapeCount;
    b2Body* body_ptr = s_Bodies.at(body);
    bool fixed_position = (body_ptr->GetType() == b2_staticBody);
    b2CircleShape circle_shape;
    circle_shape.m_p = b2Vec2(center.x, center.y);
    circle_shape.m_radius = radius;
    b2Fixture* fixture = nullptr;
    if (fixed_position) {
        fixture = body_ptr->CreateFixture(&circle_shape, 0.0f);
    }
    else {
        b2FixtureDef fixture_def;
        fixture_def.shape = &circle_shape;
        fixture_def.density = 1.0f;
        fixture_def.friction = 0.3f;
        fixture = body_ptr->CreateFixture(&fixture_def);
    }
    s_Shapes[shape_id] = fixture;
    return shape_id;
}

void PhysicsServer::set_body_linear_velocity(int32_t body, const glm::vec2& linear_velocity) {
    b2Body* body_ptr = s_Bodies.at(body);
    body_ptr->SetLinearVelocity(b2Vec2(linear_velocity.x, linear_velocity.y));
}

glm::vec2 PhysicsServer::get_body_position(int32_t body) {
    b2Body* body_ptr = s_Bodies.at(body);
    const b2Vec2& body_position = body_ptr->GetPosition();
    return { body_position.x, body_position.y };
}
