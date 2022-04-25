//
// Created by wesley on 16/04/22.
//

#ifndef UNTITLED_INPUT_HPP
#define UNTITLED_INPUT_HPP

#include <vector>

#include <glm/vec2.hpp>

class Input {
public:
    enum KeyCode {
        KEY_UNDEFINED = 0,
        ESCAPE, CONTROL, SHIFT, ALT, SUPER, ENTER,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, LEFT, RIGHT, UP, DOWN,
        KEY_COUNT
    };

    enum MouseButton {
        MB_UNDEFINED = 0,
        MB_LEFT, MB_RIGHT, MB_MIDDLE, MB_3, MB_4, MB_5,
        MB_COUNT
    };

    enum ActionName {
        ACTION_UNDEFINED = 0,
        MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT,
        CYCLE_TOOL, CYCLE_ITEM, USE,
        ACTION_COUNT
    };

    struct Action {
        // KeyCode's that activate this action
        std::vector<KeyCode> keyCodes;
        // MouseButton's that activate this action
        std::vector<MouseButton> m_MouseButtons;
    };

    static void init();
    static void update();

    static bool is_key_pressed(KeyCode keyCode);
    static bool is_key_just_pressed(KeyCode keyCode);
    static void notify_key_event(KeyCode keyCode, bool pressed);

    static glm::vec2 get_cursor_position() { return s_CursorPosition; }
    static glm::vec2 mouse_world_position();
    static bool is_mouse_button_pressed(MouseButton button);
    static bool is_mouse_button_just_pressed(MouseButton button);
    static void update_cursor_position(const glm::vec2& new_cursor_pos);
    static void notify_mouse_button_event(MouseButton button, bool pressed);

    static bool is_action_pressed(ActionName actionName);
    static bool is_action_just_pressed(ActionName actionName);

private:
    static bool s_KeysPressed[KeyCode::KEY_COUNT];
    static bool s_KeysJustPressed[KeyCode::KEY_COUNT];

    static glm::vec2 s_CursorPosition;
    static bool s_MouseButtonsPressed[MouseButton::MB_COUNT];
    static bool s_MouseButtonsJustPressed[MouseButton::MB_COUNT];

    static Action s_Actions[ActionName::ACTION_COUNT];
};


#endif //UNTITLED_INPUT_HPP
