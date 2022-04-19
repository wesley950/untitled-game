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
    s_Actions[ActionName::MOVE_UP].keyCodes = { KeyCode::W, KeyCode::UP };
    s_Actions[ActionName::MOVE_DOWN].keyCodes = { KeyCode::S, KeyCode::DOWN };
    s_Actions[ActionName::MOVE_LEFT].keyCodes = { KeyCode::A, KeyCode::LEFT };
    s_Actions[ActionName::MOVE_RIGHT].keyCodes = { KeyCode::D, KeyCode::RIGHT };
    s_Actions[ActionName::CYCLE_TOOL].keyCodes = { KeyCode::NUM_1 };
    s_Actions[ActionName::CYCLE_ITEM].keyCodes = { KeyCode::NUM_2 };
    s_Actions[ActionName::INTERACT].keyCodes = { KeyCode::F };
    s_Actions[ActionName::USE].keyCodes = { KeyCode::E };
}

void Input::update() {
    for (bool& jpk : s_KeysJustPressed) {
        jpk = false;
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
