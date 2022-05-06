//
// Created by wesley on 02/05/22.
//

#pragma once

#include "System/Components.hpp"
#include "Renderer/Texture.hpp"

#include <unordered_map>
#include <string>
#include <memory>

class ResourceManager {
public:
    static void init();
    static void shutdown();

    static std::shared_ptr<Texture> get_texture(const std::string& name);
    static std::shared_ptr<SpriteAnimatorComponent::Animation> get_sprite_animation(const std::string& name);

    static std::string resource_name(const std::string& resource_path, const std::string& resource_type_directory);

private:
    static void load_textures();
    static void load_sprite_animations();

private:
    static std::unordered_map<std::string, std::shared_ptr<Texture>> s_Textures;
    static std::unordered_map<std::string, std::shared_ptr<SpriteAnimatorComponent::Animation>> s_SpriteAnimations;
};
