//
// Created by wesley on 03/05/22.
//

#pragma once

#include <chrono>
#include <cstdint>

#include <entt/entity/registry.hpp>

class MainLoop {
public:
    static void init();
    static void update();
    static void shutdown();
    static void quit(int32_t exit_code);

    static entt::registry& get_registry() { return s_Registry; }
    static bool can_continue() { return s_CanContinue; }
    static int32_t get_exit_code() { return s_ExitCode; }

    static float get_delta_time() { return s_DeltaTime; }

private:
    static bool s_CanContinue;
    static int32_t s_ExitCode;

    static std::chrono::time_point<std::chrono::steady_clock> s_LastFrameTime;
    static float s_DeltaTime;

    static entt::registry s_Registry;
};
