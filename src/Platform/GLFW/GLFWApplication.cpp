//
// Created by wesley on 15/04/22.
//

#include "GLFWApplication.hpp"
#include "GLFWCallbacks.hpp"

#include "Core/Profiler.hpp"
#include "Renderer/Renderer.hpp"
#include "Input/Input.hpp"
#include "Resource/ResourceManager.hpp"

#include <chrono>
#include <cassert>

#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

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
        PROFILER_CLEAR();

        // Must update the input *before* polling again
        Input::update();
        glfwPollEvents();

        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> duration = now - timeAtLastFrame;
        timeAtLastFrame = now;
        deltaTime = duration.count();

        if (!m_Paused) {
            m_Scene->update(deltaTime * m_TimeScale);
        }

        glClear(GL_COLOR_BUFFER_BIT);
        m_Scene->render();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        m_Scene->draw_debug_windows(m_ShowPlayerDebugWindow);
        draw_profiler_results_window();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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

    // Init ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init();
}

void GLFWApplication::shutdown_glfw() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_Window);
    glfwTerminate();
    m_Window = nullptr;
}

void GLFWApplication::draw_profiler_results_window() {
    ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f));
    if (ImGui::Begin("##OPTIONS_WINDOW", nullptr,
                     ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoDecoration |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoNav)) {
        ImGui::Text("Debug Options");
        ImGui::DragFloat("Time Scale", &m_TimeScale, 0.01f, 0.001f, 20.0f);
        ImGui::Checkbox("Pause", &m_Paused);
        ImGui::Separator();
        ImGui::Checkbox("Show Profiler", &m_ShowProfiler);
        ImGui::Checkbox("Show Player Debugger", &m_ShowPlayerDebugWindow);
    }
    ImGui::End();

    if (m_ShowProfiler) {
        if (ImGui::Begin("Profiler")) {
            for (const auto &result: Profiler::get()->get_results()) {
                ImGui::Text("%.03f %s", result.m_ElapsedTime, result.m_Name);
            }
        }
        ImGui::End();
    }
}

Application* create_application() {
    return new GLFWApplication();
}
