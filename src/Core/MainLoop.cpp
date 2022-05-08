//
// Created by wesley on 03/05/22.
//

#include "MainLoop.hpp"

#include "Server/PhysicsServer.hpp"
#include "System/PlayerSystem.hpp"
#include "System/GraphicsSystem.hpp"

#include "Resource/ResourceManager.hpp"
#include "Input/Input.hpp"

bool MainLoop::s_CanContinue = false;
int32_t MainLoop::s_ExitCode = 0;

std::chrono::time_point<std::chrono::steady_clock> MainLoop::s_LastFrameTime {};
float MainLoop::s_DeltaTime = 0.0f;

entt::registry MainLoop::s_Registry {};

void MainLoop::init() {
    ResourceManager::init();
    Input::init();

    GraphicsSystem::init();
    PlayerSystem::init();

    s_CanContinue = true;
    s_LastFrameTime = std::chrono::steady_clock::now();
}

void MainLoop::update() {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> duration = (now - s_LastFrameTime);
    s_LastFrameTime = now;
    s_DeltaTime = duration.count();

    PlayerSystem::update();
    PhysicsServer::update();
    GraphicsSystem::submit();

    // Clear the inputs received this frame before polling again on the next
    Input::update();
}

void MainLoop::shutdown() {
    // NOTE: must clear the registry before doing anything else because
    // this will call the "destructor" of components and thus release
    // any resources (textures, audio files, etc.) that they hold.
    // Otherwise, this will happen on the "final stages of termination"
    // of the application, where most of the resources are already on an
    // invalid state.

    s_Registry = {};
    ResourceManager::shutdown();
}

void MainLoop::quit(int32_t exit_code) {
    s_CanContinue = false;
    s_ExitCode = exit_code;
}
