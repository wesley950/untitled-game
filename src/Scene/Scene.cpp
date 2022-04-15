//
// Created by wesley on 15/04/22.
//

#include "Scene.hpp"
#include "Components.hpp"
#include "Renderer/Renderer.hpp"

void Scene::start() {
    create_basic();
}

void Scene::update(float deltaTime) {
    m_Registry.view<TransformComponent>().each([&deltaTime] (auto entity, TransformComponent& tc) {
        tc.m_Rotation += deltaTime * 15.0f;
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
