cmake_minimum_required(VERSION 3.22)


# Project settings
project(farming_game)
set(CMAKE_CXX_STANDARD 17)


# Project files
set(CORE_FILES
        src/Core/UUID.cpp src/Core/UUID.hpp
        src/Core/Timer.cpp src/Core/Timer.hpp
        src/Core/Profiler.cpp src/Core/Profiler.hpp
        src/Core/MainLoop.cpp src/Core/MainLoop.hpp)
set(INPUT_FILES
        src/Input/Input.cpp src/Input/Input.hpp)
set(SERVER_FILES
        src/Server/RenderingServer.cpp src/Server/RenderingServer.hpp
        src/Server/DisplayServer.cpp src/Server/DisplayServer.hpp
        src/Server/PhysicsServer.cpp src/Server/PhysicsServer.hpp)
set(SYSTEM_FILES
        src/System/PlayerSystem.cpp src/System/PlayerSystem.hpp
        src/System/SceneSystem.cpp src/System/SceneSystem.hpp
        src/System/GraphicsSystem.cpp src/System/GraphicsSystem.hpp)
set(RESOURCE_FILES
        src/Resource/ResourceManager.cpp src/Resource/ResourceManager.hpp src/Resource/Texture.cpp src/Resource/Texture.hpp src/Resource/SpriteAnimation.cpp src/Resource/SpriteAnimation.hpp)
set(BOX2D_PLATFORM_FILES
        src/Platform/Box2D/Box2DPhysicsServer.cpp)
set(GLFW_PLATFORM_FILES
        src/Platform/GLFW/GLFWCallbacks.cpp src/Platform/GLFW/GLFWCallbacks.hpp
        src/Platform/GLFW/GLFWDisplayServer.cpp)
set(GL3_PLATFORM_FILES
        src/Platform/GL3/GL3RenderingServer.cpp)
set(GLAD_FILES
        thirdparty/glad/glad.c thirdparty/glad/glad.h
        thirdparty/glad/khrplatform.h)
set(IMGUI_FILES
        thirdparty/imgui/imconfig.h thirdparty/imgui/imgui.cpp thirdparty/imgui/imgui.h
        thirdparty/imgui/imgui_demo.cpp thirdparty/imgui/imgui_draw.cpp thirdparty/imgui/imgui_internal.h
        thirdparty/imgui/imgui_tables.cpp thirdparty/imgui/imgui_widgets.cpp
        thirdparty/imgui/imstb_rectpack.h thirdparty/imgui/imstb_textedit.h thirdparty/imgui/imstb_truetype.h
        thirdparty/imgui/backends/imgui_impl_glfw.h thirdparty/imgui/backends/imgui_impl_glfw.cpp
        thirdparty/imgui/backends/imgui_impl_opengl3.h thirdparty/imgui/backends/imgui_impl_opengl3.cpp)


# Targets
add_executable(farming_game
        src/Main.cpp
        ${CORE_FILES} ${INPUT_FILES} ${SERVER_FILES} ${SYSTEM_FILES} ${RESOURCE_FILES}
        ${BOX2D_PLATFORM_FILES} ${GLFW_PLATFORM_FILES} ${GL3_PLATFORM_FILES}
        ${GLAD_FILES} ${IMGUI_FILES})


# Include directories
target_include_directories(farming_game PUBLIC
        src/
        thirdparty thirdparty/stb thirdparty/imgui)


# Thirdparty libraries

# GLFW

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw)
target_link_libraries(farming_game glfw)

# GLM (maths)

add_subdirectory(thirdparty/glm)
target_link_libraries(farming_game glm::glm)

# EnTT (ECS)

add_subdirectory(thirdparty/entt)
target_link_libraries(farming_game EnTT::EnTT)

# Box2D (2D physics)

set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/box2d)
target_link_libraries(farming_game box2d)

# JSON (by nlohmann)

add_subdirectory(thirdparty/json)
target_link_libraries(farming_game nlohmann_json)