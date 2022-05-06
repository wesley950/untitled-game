//
// Created by wesley on 16/04/22.
//

#include "Input.hpp"
#include "Server/RenderingServer.hpp"

#include <functional>

bool Input::s_KeysPressed[KeyCode::KEY_COUNT];
bool Input::s_KeysJustPressed[KeyCode::KEY_COUNT];

glm::vec2 Input::s_CursorPosition { 0.0f, 0.0f };
bool Input::s_MouseButtonsPressed[MouseButton::MB_COUNT];
bool Input::s_MouseButtonsJustPressed[MouseButton::MB_COUNT];

Input::Action Input::s_Actions[ActionName::ACTION_COUNT];

void Input::init() {
    for (int i = 0;i < KeyCode::KEY_COUNT;i++) {
        s_KeysPressed[i] = false;
        s_KeysJustPressed[i] = false;
    }

    for (int i = 0;i < MouseButton::MB_COUNT;i++) {
        s_MouseButtonsPressed[i] = false;
        s_MouseButtonsJustPressed[i] = false;
    }

    // Sets up the actions
    s_Actions[ActionName::MOVE_UP].keyCodes = { KeyCode::W, KeyCode::UP };
    s_Actions[ActionName::MOVE_DOWN].keyCodes = { KeyCode::S, KeyCode::DOWN };
    s_Actions[ActionName::MOVE_LEFT].keyCodes = { KeyCode::A, KeyCode::LEFT };
    s_Actions[ActionName::MOVE_RIGHT].keyCodes = { KeyCode::D, KeyCode::RIGHT };

    s_Actions[ActionName::CYCLE_TOOL].keyCodes = { KeyCode::NUM_1 };
    s_Actions[ActionName::CYCLE_ITEM].keyCodes = { KeyCode::NUM_2 };

    s_Actions[ActionName::USE].keyCodes = { KeyCode::E };
    s_Actions[ActionName::USE].m_MouseButtons = { MouseButton::MB_RIGHT };
}

void Input::update() {
    for (bool& jpk : s_KeysJustPressed) {
        jpk = false;
    }

    for (bool& jpmb : s_MouseButtonsJustPressed) {
        jpmb = false;
    }
}

bool Input::is_key_pressed(KeyCode keyCode) {
    return s_KeysPressed[keyCode];
}

bool Input::is_key_just_pressed(KeyCode keyCode) {
    return s_KeysJustPressed[keyCode];
}

void Input::notify_key_event(KeyCode keyCode, bool pressed) {
    s_KeysPressed[keyCode] = pressed;
    s_KeysJustPressed[keyCode] = pressed;
}

glm::vec2 Input::mouse_world_position() {
    return RenderingServer::screen_to_world_position(get_cursor_position());
}

bool Input::is_mouse_button_pressed(MouseButton button) {
    return s_MouseButtonsPressed[button];
}

bool Input::is_mouse_button_just_pressed(MouseButton button) {
    return s_MouseButtonsJustPressed[button];
}

void Input::update_cursor_position(const glm::vec2& new_cursor_pos) {
    s_CursorPosition = new_cursor_pos;
}

void Input::notify_mouse_button_event(MouseButton button, bool pressed) {
    s_MouseButtonsPressed[button] = pressed;
    s_MouseButtonsJustPressed[button] = pressed;
}

bool Input::is_action_pressed(Input::ActionName actionName) {
    auto& action = s_Actions[actionName];

    // Check for all possible assigned keys
    if (std::any_of(action.keyCodes.begin(), action.keyCodes.end(), [] (KeyCode kc) { return is_key_pressed(kc); })) {
        return true;
    }

    // Then for mouse buttons
    if (std::any_of(action.m_MouseButtons.begin(), action.m_MouseButtons.end(), [&](const auto &item) { return is_mouse_button_pressed(item); })) {
        return true;
    }

    return false;
}

bool Input::is_action_just_pressed(Input::ActionName actionName) {
    auto& action = s_Actions[actionName];

    // Check for all possible assigned keys
    if (std::any_of(action.keyCodes.begin(), action.keyCodes.end(), [] (KeyCode kc) { return is_key_just_pressed(kc); })) {
        return true;
    }

    // Then for mouse buttons
    if (std::any_of(action.m_MouseButtons.begin(), action.m_MouseButtons.end(), [&](const auto &item) { return is_mouse_button_just_pressed(item); })) {
        return true;
    }

    return false;
}
