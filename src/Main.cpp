#include "Core/Application.hpp"

int main() {
    auto* app = create_application();
    app->run();
    delete app;
    return 0;
}
