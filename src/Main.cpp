#include "Server/DisplayServer.hpp"
#include "Server/PhysicsServer.hpp"
#include "Server/RenderingServer.hpp"
#include "Core/MainLoop.hpp"

int main() {
    DisplayServer::init("Farming Game", 1280, 720);
    PhysicsServer::init();
    RenderingServer::init();
    MainLoop::init();

    while (MainLoop::can_continue()) {
        DisplayServer::poll_events();

        MainLoop::update();
        RenderingServer::flush();

        DisplayServer::present();
    }
    MainLoop::shutdown();

    RenderingServer::shutdown();
    PhysicsServer::shutdown();
    DisplayServer::shutdown();

    return MainLoop::get_exit_code();
}
