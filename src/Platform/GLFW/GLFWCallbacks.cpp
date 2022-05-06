//
// Created by wesley on 15/04/22.
//

#include "GLFWCallbacks.hpp"

#include "Core/MainLoop.hpp"
#include "Input/Input.hpp"
#include "Server/RenderingServer.hpp"

#include <glad/glad.h>

void window_close_callback(GLFWwindow* window) {
    MainLoop::quit(0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    RenderingServer::set_viewport_size({ (float)width, (float)height });
}

static Input::KeyCode glfwToKC(int glfwKeyCode) {
    switch (glfwKeyCode) {
        case GLFW_KEY_ESCAPE:
            return Input::KeyCode::ESCAPE;

        case GLFW_KEY_LEFT_CONTROL:
        case GLFW_KEY_RIGHT_CONTROL:
            return Input::KeyCode::CONTROL;

        case GLFW_KEY_LEFT_SHIFT:
        case GLFW_KEY_RIGHT_SHIFT:
            return Input::KeyCode::SHIFT;

        case GLFW_KEY_LEFT_ALT:
        case GLFW_KEY_RIGHT_ALT:
            return Input::KeyCode::ALT;

        case GLFW_KEY_LEFT_SUPER:
        case GLFW_KEY_RIGHT_SUPER:
            return Input::KeyCode::SUPER;

        case GLFW_KEY_KP_ENTER:
        case GLFW_KEY_ENTER:
            return Input::KeyCode::ENTER;

        case GLFW_KEY_UP:
            return Input::KeyCode::UP;

        case GLFW_KEY_DOWN:
            return Input::KeyCode::DOWN;

        case GLFW_KEY_LEFT:
            return Input::KeyCode::LEFT;

        case GLFW_KEY_RIGHT:
            return Input::KeyCode::RIGHT;

        default:
        {
            if (glfwKeyCode >= GLFW_KEY_KP_0 && glfwKeyCode <= GLFW_KEY_KP_9) {
                return (Input::KeyCode)(Input::KeyCode::NUM_9 - (GLFW_KEY_KP_9 - glfwKeyCode));
            } else if (glfwKeyCode >= GLFW_KEY_0 && glfwKeyCode <= GLFW_KEY_9) {
                return (Input::KeyCode)(Input::KeyCode::NUM_9 - (GLFW_KEY_9 - glfwKeyCode));
            } else if (glfwKeyCode >= GLFW_KEY_A && glfwKeyCode <= GLFW_KEY_Z) {
                return (Input::KeyCode)(Input::KeyCode::Z - (GLFW_KEY_Z - glfwKeyCode));
            }
        }
    }

    return Input::KeyCode::KEY_UNDEFINED;
}

void key_callback(GLFWwindow* window, int keycode, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        Input::KeyCode kc = glfwToKC(keycode);
        Input::notify_key_event(kc, true);
    }
    else if (action == GLFW_RELEASE) {
        Input::KeyCode kc = glfwToKC(keycode);
        Input::notify_key_event(kc, false);
    }
}

void cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos) {
    auto cursor_x = (float) x_pos;
    auto cursor_y = (float) y_pos;
    Input::update_cursor_position({ cursor_x, cursor_y });
}

static Input::MouseButton glfw_to_mb(int glfw_mb) {
    switch (glfw_mb) {
        case GLFW_MOUSE_BUTTON_LEFT:
            return Input::MouseButton::MB_LEFT;

        case GLFW_MOUSE_BUTTON_RIGHT:
            return Input::MouseButton::MB_RIGHT;

        case GLFW_MOUSE_BUTTON_MIDDLE:
            return Input::MouseButton::MB_MIDDLE;

        case GLFW_MOUSE_BUTTON_4:
            return Input::MouseButton::MB_3;

        case GLFW_MOUSE_BUTTON_5:
            return Input::MouseButton::MB_4;

        case GLFW_MOUSE_BUTTON_6:
            return Input::MouseButton::MB_5;
    }

    return Input::MouseButton::MB_UNDEFINED;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Input::MouseButton mb = glfw_to_mb(button);

    if (action == GLFW_PRESS) {
        Input::notify_mouse_button_event(mb, true);
    }
    else if (action == GLFW_RELEASE) {
        Input::notify_mouse_button_event(mb, false);
    }
}
