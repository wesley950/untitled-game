//
// Created by wesley on 15/04/22.
//

#include "GLFWApplication.hpp"
#include "GLFWCallbacks.hpp"

#include "Renderer/Renderer.hpp"
#include "Input/Input.hpp"
#include "Resource/ResourceManager.hpp"

#include <chrono>
#include <cassert>

#include <glad/glad.h>

GLFWApplication::GLFWApplication() {
    assert(s_Instance == nullptr);
    s_Instance = this;
}

void GLFWApplication::run() {
    init_glfw();
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    Input::init();
    Renderer::init();
    ResourceManager::init();

    m_TimeStep = 1.0f / 60.0f;
    m_Scene = new Scene();
    m_Scene->start();

    float deltaTime = 0.0f;
    auto timeAtLastFrame = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(m_Window)) {
        // Must update the input *before* polling again
        Input::update();
        glfwPollEvents();

        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> duration = now - timeAtLastFrame;
        timeAtLastFrame = now;
        deltaTime = duration.count();

        m_Scene->update(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT);
        m_Scene->render();

        glfwSwapBuffers(m_Window);
    }
    m_Scene->release();
    delete m_Scene;
    m_Scene = nullptr;

    Renderer::shutdown();

    shutdown_glfw();
}

void GLFWApplication::init_glfw() {
    glfwInit();
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    m_Window = glfwCreateWindow(1280, 720, "untitled", nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(0);

    // GLFW callbacks
    {
        glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

        glfwSetKeyCallback(m_Window, key_callback);

        glfwSetCursorPosCallback(m_Window, cursor_position_callback);
        glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
    }
}

void GLFWApplication::shutdown_glfw() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
    m_Window = nullptr;
}

Application* create_application() {
    return new GLFWApplication();
}
