//
// Created by wesley on 15/04/22.
//

#include "Scene.hpp"
#include "Components.hpp"
#include "Renderer/Renderer.hpp"

void Scene::start() {
    auto basic = create_basic("Basic");
    auto& sprite = basic.get<SpriteComponent>();
    sprite.m_Color = { 0.1f, 0.5f, 0.1f, 1.0f };
    auto& transform = basic.get<TransformComponent>();
    transform.m_Position = { 1.0f, 0.0f };

    auto basic2 = create_basic("Basic2");
    auto& sprite2 = basic2.get<SpriteComponent>();
    sprite2.m_Color = { 1.0f, 0.3f, 0.7f, 1.0f };
    auto& transform2 = basic2.get<TransformComponent>();
    transform2.m_Position = { 0.0f, 1.0f };
}

void Scene::update(float deltaTime) {
    m_Registry.view<TransformComponent>().each([&deltaTime] (auto entity, TransformComponent& tc) {
        tc.m_Rotation += deltaTime * 1.0f;
    });
}

void Scene::render() {
    Renderer::begin_frame();
    Renderer::prepare(Renderer::RenderMode::Y_SORTED_SPRITES);
    m_Registry.view<TransformComponent, SpriteComponent>().each([] (auto entity, TransformComponent& tc, SpriteComponent& sc) {
        Renderer::draw_quad(tc.get_transformation(), sc.m_Size, sc.m_Center, sc.m_Color);
    });
    Renderer::present();
}

void Scene::release() {

}

entt::handle Scene::create_basic(const std::string& tag) {
    auto basic = entt::handle(m_Registry, m_Registry.create());
    basic.emplace<TagComponent>(tag);
    basic.emplace<UUIDComponent>();
    basic.emplace<TransformComponent>();
    basic.emplace<SpriteComponent>();
    return basic;
}
