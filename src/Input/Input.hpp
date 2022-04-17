//
// Created by wesley on 16/04/22.
//

#ifndef UNTITLED_INPUT_HPP
#define UNTITLED_INPUT_HPP

#include <vector>

class Input {
public:
    enum KeyCode {
        KEY_UNDEFINED = 0,
        ESCAPE, CONTROL, SHIFT, ALT, SUPER, ENTER,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, LEFT, RIGHT, UP, DOWN,
        KEY_COUNT
    };

    enum ActionName {
        ACTION_UNDEFINED = 0,
        MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT,
        ACTION_COUNT
    };

    struct Action {
        // KeyCode's that activate this action
        std::vector<KeyCode> keyCodes;
    };

    static void init();
    static void update();

    static bool is_key_pressed(KeyCode keyCode);
    static bool is_key_just_pressed(KeyCode keyCode);
    static void notify_key_event(KeyCode keyCode, bool pressed);

    static bool is_action_pressed(ActionName actionName);
    static bool is_action_just_pressed(ActionName actionName);

private:
    static bool s_KeysPressed[KeyCode::KEY_COUNT];
    static bool s_KeysJustPressed[KeyCode::KEY_COUNT];
    static Action s_Actions[ActionName::ACTION_COUNT];
};


#endif //UNTITLED_INPUT_HPP
