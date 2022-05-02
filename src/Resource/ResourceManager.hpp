//
// Created by wesley on 02/05/22.
//

#pragma once

#include "Scene/Components.hpp"

#include <unordered_map>
#include <string>
#include <memory>

class ResourceManager {
public:
    static void init();
    static void shutdown();

    static std::shared_ptr<SpriteAnimatorComponent::Animation> get_sprite_animation(const std::string& name);

private:
    static void load_sprite_animations();

private:
    static std::unordered_map<std::string, std::shared_ptr<SpriteAnimatorComponent::Animation>> s_SpriteAnimations;
};
