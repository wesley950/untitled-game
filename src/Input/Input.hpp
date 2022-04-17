//
// Created by wesley on 16/04/22.
//

#ifndef UNTITLED_INPUT_HPP
#define UNTITLED_INPUT_HPP


class Input {
public:
    enum KeyCode {
        UNDEFINED = 0,
        ESCAPE, CONTROL, SHIFT, ALT, SUPER, ENTER,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, LEFT, RIGHT, UP, DOWN,
        KEY_COUNT
    };

    static void init();

    static bool is_key_pressed(KeyCode keyCode);
    static void notify_key_event(KeyCode keyCode, bool pressed);

private:
    static bool s_KeysPressed[KeyCode::KEY_COUNT];
};


#endif //UNTITLED_INPUT_HPP
