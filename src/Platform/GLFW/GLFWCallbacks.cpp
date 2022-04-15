//
// Created by wesley on 15/04/22.
//

#include "GLFWCallbacks.hpp"
#include <glad/glad.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // WorldRenderer::ResizeFramebuffer(width, height);
}

void key_callback(GLFWwindow* window, int keycode, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_RELEASE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
