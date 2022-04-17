//
// Created by wesley on 15/04/22.
//

#include "GLFWApplication.hpp"
#include "GLFWCallbacks.hpp"

#include "Renderer/Renderer.hpp"
#include "Input/Input.hpp"

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

    m_TimeStep = 1.0f / 60.0f;
    m_Scene = new Scene();
    m_Scene->start();

    while (!glfwWindowShouldClose(m_Window)) {
        glfwPollEvents();

        m_Scene->update(m_TimeStep);

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    m_Window = glfwCreateWindow(1280, 720, "untitled", nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
    glfwSetKeyCallback(m_Window, key_callback);
}

void GLFWApplication::shutdown_glfw() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
    m_Window = nullptr;
}

Application* create_application() {
    return new GLFWApplication();
}
