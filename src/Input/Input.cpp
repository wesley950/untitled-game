//
// Created by wesley on 16/04/22.
//

#include "Input.hpp"

#include <functional>

bool Input::s_KeysPressed[KeyCode::KEY_COUNT];
bool Input::s_KeysJustPressed[KeyCode::KEY_COUNT];
Input::Action Input::s_Actions[ActionName::ACTION_COUNT];

void Input::init() {
    for (int i = 0;i < KeyCode::KEY_COUNT;i++) {
        s_KeysPressed[i] = false;
        s_KeysJustPressed[i] = false;
    }

    // Sets up the actions
    s_Actions[ActionName::MOVE_UP].keyCodes.push_back(KeyCode::W);
    s_Actions[ActionName::MOVE_UP].keyCodes.push_back(KeyCode::UP);
    s_Actions[ActionName::MOVE_DOWN].keyCodes.push_back(KeyCode::S);
    s_Actions[ActionName::MOVE_DOWN].keyCodes.push_back(KeyCode::DOWN);
    s_Actions[ActionName::MOVE_LEFT].keyCodes.push_back(KeyCode::A);
    s_Actions[ActionName::MOVE_LEFT].keyCodes.push_back(KeyCode::LEFT);
    s_Actions[ActionName::MOVE_RIGHT].keyCodes.push_back(KeyCode::D);
    s_Actions[ActionName::MOVE_RIGHT].keyCodes.push_back(KeyCode::RIGHT);
}

void Input::update() {
    for (bool& jp : s_KeysJustPressed) {
        jp = false;
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

bool Input::is_action_pressed(Input::ActionName actionName) {
    // TODO: take into account gamepad buttons and what not too
    auto& action = s_Actions[actionName];
    return std::any_of(action.keyCodes.begin(), action.keyCodes.end(), [] (KeyCode kc) { return is_key_pressed(kc); }); // Weird Clang-tidy suggestion
}

bool Input::is_action_just_pressed(Input::ActionName actionName) {
    // TODO: take into account gamepad buttons and what not too
    auto& action = s_Actions[actionName];
    return std::any_of(action.keyCodes.begin(), action.keyCodes.end(), [] (KeyCode kc) { return is_key_just_pressed(kc); }); // Weird Clang-tidy suggestion
}
