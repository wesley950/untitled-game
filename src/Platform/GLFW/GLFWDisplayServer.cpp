//
// Created by wesley on 03/05/22.
//

#include "Server/DisplayServer.hpp"
#include "GLFWCallbacks.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

static GLFWwindow* s_Window = nullptr;

void DisplayServer::init(const char* title, int32_t width, int32_t height) {
    glfwInit();
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    s_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(s_Window);
    glfwSwapInterval(0);

    // GLFW callbacks
    {
        glfwSetWindowCloseCallback(s_Window, window_close_callback);
        glfwSetFramebufferSizeCallback(s_Window, framebuffer_size_callback);

        glfwSetKeyCallback(s_Window, key_callback);
        glfwSetCursorPosCallback(s_Window, cursor_position_callback);
        glfwSetMouseButtonCallback(s_Window, mouse_button_callback);
    }
}

void DisplayServer::poll_events() {
    glfwPollEvents();
}

void DisplayServer::present() {
    glfwSwapBuffers(s_Window);
}

void DisplayServer::shutdown() {
    glfwDestroyWindow(s_Window);
    glfwTerminate();
    s_Window = nullptr;
}
