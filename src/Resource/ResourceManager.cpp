//
// Created by wesley on 02/05/22.
//

#include "ResourceManager.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

#include <nlohmann/json.hpp>

std::unordered_map<std::string, std::shared_ptr<Texture>> ResourceManager::s_Textures {};
std::unordered_map<std::string, std::shared_ptr<SpriteAnimatorComponent::Animation>> ResourceManager::s_SpriteAnimations {};

void ResourceManager::init() {
    load_textures();
    load_sprite_animations();
}

void ResourceManager::shutdown() {
    // NOTE: its necessary to shutdown RenderingServer or ResourceManager
    // so the textures can actually be deleted before the application is
    // on its final stages of termination because at that point, most (if
    // not all) static objects are apparently already deconstructed.
    s_Textures = {};
    s_SpriteAnimations = {};
}

std::shared_ptr<Texture> ResourceManager::get_texture(const std::string& name) {
    return s_Textures.at(name);
}

std::shared_ptr<SpriteAnimatorComponent::Animation> ResourceManager::get_sprite_animation(const std::string& name) {
    return s_SpriteAnimations.at(name);
}

void ResourceManager::load_textures() {
    const std::filesystem::path TEXTURES_PATH = std::filesystem::path("data/textures");

    for (const auto& entry : std::filesystem::recursive_directory_iterator(TEXTURES_PATH)) {
        if (entry.is_regular_file()) {
            auto texture_ref = std::make_shared<Texture>(entry.path().string());
            s_Textures[resource_name(entry.path(), TEXTURES_PATH)] = texture_ref;
        }
    }
}

void ResourceManager::load_sprite_animations() {
    const std::filesystem::path SPRITE_ANIMATIONS_PATH = std::filesystem::path("data/sprite_animations");

    for (const auto& entry : std::filesystem::recursive_directory_iterator(SPRITE_ANIMATIONS_PATH)) {
        if (entry.is_regular_file()) {
            std::ifstream file_stream(entry.path().string());
            if (file_stream.is_open()) {
                std::stringstream stream;
                stream << file_stream.rdbuf();
                file_stream.close();

                nlohmann::json json_document = nlohmann::json::from_bson(stream.str());
                auto& variants_object = json_document["variants"];
                auto sac_anim = std::make_shared<SpriteAnimatorComponent::Animation>();

                for (auto itr = variants_object.begin();itr != variants_object.end();itr++) {
                    auto& variant_name = itr.key();
                    auto& variant_object = itr.value();

                    auto anim_variant = std::make_shared<SpriteAnimatorComponent::Animation::Variant>();
                    sac_anim->m_Variants[variant_name] = anim_variant;

                    anim_variant->m_AdvanceSpeed = variant_object["advance_speed"].get<float>();
                    anim_variant->m_HorizontalFrames = variant_object["horizontal_frames"].get<int32_t>();
                    anim_variant->m_VerticalFrames = variant_object["vertical_frames"].get<int32_t>();

                    auto& frames = variant_object["frames"];
                    for (const auto& frame : frames) {
                        anim_variant->m_Frames.push_back({
                                                                frame["x"].get<int32_t>(),
                                                                frame["y"].get<int32_t>()
                                                        });
                    }
                }

                s_SpriteAnimations[resource_name(entry.path(), SPRITE_ANIMATIONS_PATH)] = sac_anim;
            }
        }
    }
}

std::string ResourceManager::resource_name(const std::string& resource_path, const std::string& resource_type_directory) {
    return std::filesystem::relative(resource_path, resource_type_directory).replace_extension().string();
}
