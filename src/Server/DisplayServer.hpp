//
// Created by wesley on 03/05/22.
//

#pragma once

#include <cstdint>

class DisplayServer {
public:
    static void init(const char* title, int32_t width, int32_t height);
    static void poll_events();
    static void present();
    static void shutdown();
};
