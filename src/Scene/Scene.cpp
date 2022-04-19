//
// Created by wesley on 15/04/22.
//

#include "Scene.hpp"
#include "Components.hpp"
#include "Renderer/Renderer.hpp"

void Scene::start() {
    m_PhysicsWorld = new b2World(b2Vec2(0.0f, 0.0f));

    // Create all the initial entities
    populate();

    // Assign physics bodies to components
    {
        m_Registry.view<PhysicsBodyComponent, TransformComponent>().each([this](auto entity, auto &pbc, auto &tc) {
            // Create the physics body
            b2BodyDef bodyDef;
            bodyDef.type = (pbc.m_FixedPosition) ? b2_staticBody : b2_dynamicBody;
            bodyDef.position.Set(tc.m_Position.x, tc.m_Position.y);
            bodyDef.fixedRotation = true;
            pbc.m_Handle = m_PhysicsWorld->CreateBody(&bodyDef);
        });
    }

    // Assign collision shapes to components
    {
        m_Registry.view<PhysicsBodyComponent, PhysicsShapeListComponent>().each([](auto entity, auto &pbc, auto &pslc) {
            std::vector<PhysicsShapeListComponent::ShapeDefinition> &sdl = pslc.m_ShapeDefs;

            const auto create_collider_static = [](b2Shape *shapePtr, b2Body *bodyPtr) {
                return bodyPtr->CreateFixture(shapePtr, 0.0f);
            };

            const auto create_collider_dyn_or_kin = [](b2Shape *shapePtr, b2Body *bodyPtr) {
                b2FixtureDef fixtureDef;
                fixtureDef.shape = shapePtr;
                fixtureDef.density = 1.0f;
                fixtureDef.friction = 0.3f;
                return bodyPtr->CreateFixture(&fixtureDef);
            };

            for (auto &shapeDef: sdl) {
                switch (shapeDef.m_Type) {
                    case PhysicsShapeListComponent::ST_SPHERE: {
                        b2CircleShape circle;
                        circle.m_radius = glm::length(shapeDef.m_HalfExtents);
                        circle.m_p.Set(shapeDef.m_Center.x, shapeDef.m_Center.y);

                        if (pbc.m_FixedPosition)
                            pslc.m_ShapeHandles.push_back(create_collider_static(&circle, pbc.m_Handle));
                        else
                            pslc.m_ShapeHandles.push_back(create_collider_dyn_or_kin(&circle, pbc.m_Handle));

                        break;
                    }

                    case PhysicsShapeListComponent::ST_RECTANGLE: {
                        b2PolygonShape rectangle;
                        rectangle.SetAsBox(shapeDef.m_HalfExtents.x, shapeDef.m_HalfExtents.y,
                                           b2Vec2(shapeDef.m_Center.x, shapeDef.m_Center.y), 0.0f);

                        if (pbc.m_FixedPosition)
                            pslc.m_ShapeHandles.push_back(create_collider_static(&rectangle, pbc.m_Handle));
                        else
                            pslc.m_ShapeHandles.push_back(create_collider_dyn_or_kin(&rectangle, pbc.m_Handle));

                        break;
                    }
                }
            }
        });
    }
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
    Renderer::begin_frame();
    Renderer::prepare(Renderer::RenderMode::Y_SORTED_SPRITES);

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

//    m_Registry.view<TransformComponent, SpriteComponent>().each(
//            [](auto entity, TransformComponent &tc, SpriteComponent &sc) {
//                Renderer::draw_quad(tc.get_transformation(), sc.m_Size, sc.m_Center, sc.m_Color);
//            });
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
    basic.emplace<SpriteComponent>();
    return basic;
}

void Scene::populate() {
    create_player();

    // creates a few static boxes
    {
        for (int x = 0; x < 10; x++) {
            auto staticBox = create_basic();
            auto &pbc = staticBox.emplace<PhysicsBodyComponent>(true);
            auto &pslc = staticBox.emplace<PhysicsShapeListComponent>();

            pslc.m_ShapeDefs = {{{0.5f, 0.5f}, {0.0f, 0.0f},
                                 (x % 3 != 0) ? PhysicsShapeListComponent::ShapeType::ST_SPHERE
                                              : PhysicsShapeListComponent::ShapeType::ST_RECTANGLE}};

            auto &tc = staticBox.get<TransformComponent>();
            tc.m_Position.x = (float) x * 1.15f;
        }
    }
}
