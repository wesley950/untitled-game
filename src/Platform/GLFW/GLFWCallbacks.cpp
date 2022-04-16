//
// Created by wesley on 15/04/22.
//

#include "GLFWCallbacks.hpp"
#include "Renderer/Renderer.hpp"
#include <glad/glad.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Renderer::set_viewport_size({ (float)width, (float) height });
}

void key_callback(GLFWwindow* window, int keycode, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_RELEASE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
