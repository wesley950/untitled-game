//
// Created by wesley on 02/05/22.
//

#include "ResourceManager.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

#include <nlohmann/json.hpp>

std::unordered_map<std::string, std::shared_ptr<SpriteAnimatorComponent::Animation>> ResourceManager::s_SpriteAnimations {};

void ResourceManager::init() {
    load_sprite_animations();
}

void ResourceManager::shutdown() {

}

std::shared_ptr<SpriteAnimatorComponent::Animation> ResourceManager::get_sprite_animation(const std::string& name) {
    return s_SpriteAnimations.at(name);
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
                auto sac_anim = std::make_shared<SpriteAnimatorComponent::Animation>();

                sac_anim->m_AdvanceSpeed = json_document["advance_speed"].get<float>();
                sac_anim->m_HorizontalFrames = json_document["horizontal_frames"].get<int32_t>();
                sac_anim->m_VerticalFrames = json_document["vertical_frames"].get<int32_t>();

                const auto& frames = json_document["frames"];
                for (const auto& frame : frames) {
                    sac_anim->m_Frames.push_back({
                         frame["x"].get<int32_t>(),
                         frame["y"].get<int32_t>()
                    });
                }

                auto resource_name = std::filesystem::relative(entry.path(), SPRITE_ANIMATIONS_PATH).replace_extension().string();
                s_SpriteAnimations[resource_name] = sac_anim;
            }
        }
    }
}
