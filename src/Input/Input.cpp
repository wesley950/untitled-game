//
// Created by wesley on 16/04/22.
//

#include "Input.hpp"

bool Input::s_KeysPressed[KeyCode::KEY_COUNT];

void Input::init() {
    // Clang-tidy bullshit \/
    for (bool & i : s_KeysPressed) {
        i = false;
    }
}

bool Input::is_key_pressed(KeyCode keyCode) {
    return s_KeysPressed[keyCode];
}

void Input::notify_key_event(KeyCode keyCode, bool pressed) {
    s_KeysPressed[keyCode] = pressed;
}
