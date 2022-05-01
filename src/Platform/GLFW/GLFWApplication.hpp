//
// Created by wesley on 15/04/22.
//

#pragma once

#include "Core/Application.hpp"
#include "Scene/Scene.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class GLFWApplication : public Application {
public:
    GLFWApplication();
    ~GLFWApplication() override = default;
    void run() override;

private:
    void init_glfw();
    void shutdown_glfw();

private:
    GLFWwindow* m_Window = nullptr;

    float m_TimeStep = 0.0f;
    Scene* m_Scene = nullptr;
};
