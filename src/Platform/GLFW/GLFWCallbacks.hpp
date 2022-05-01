//
// Created by wesley on 15/04/22.
//

#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void key_callback(GLFWwindow*, int keycode, int scancode, int action, int mods);

void cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
