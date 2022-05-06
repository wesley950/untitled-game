//
// Created by wesley on 03/05/22.
//

#include "SceneSystem.hpp"
#include "Components.hpp"

#include "Core/MainLoop.hpp"

entt::handle SceneSystem::create_entity() {
    entt::handle created_entity { MainLoop::get_registry(), MainLoop::get_registry().create() };
    created_entity.emplace<TransformComponent>();
    return created_entity;
}
