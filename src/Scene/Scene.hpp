//
// Created by wesley on 15/04/22.
//

#ifndef UNTITLED_SCENE_HPP
#define UNTITLED_SCENE_HPP

#include <string>

#include <entt/entt.hpp>

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    void start();
    void update(float deltaTime);
    void render();
    void release();

    entt::handle create_basic(const std::string& tag = "Basic Actor");

private:
    entt::registry m_Registry {};
};


#endif //UNTITLED_SCENE_HPP
