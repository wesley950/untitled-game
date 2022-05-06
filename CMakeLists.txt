cmake_minimum_required(VERSION 3.22)
project(farming_game)

set(CMAKE_CXX_STANDARD 17)

set(CORE_FILES
        src/Core/Application.hpp src/Core/Application.cpp
        src/Core/UUID.cpp src/Core/UUID.hpp
        src/Core/MathUtils.hpp
        src/Core/Timer.hpp src/Core/Timer.cpp
        src/Core/Profiler.cpp src/Core/Profiler.hpp
        src/Core/MainLoop.cpp src/Core/MainLoop.hpp)
set(INPUT_FILES
        src/Input/Input.cpp src/Input/Input.hpp)
set(RENDERER_FILES
        src/Renderer/Renderer.cpp src/Renderer/Renderer.hpp
        src/Renderer/VertexArray.cpp src/Renderer/VertexArray.hpp
        src/Renderer/Shader.cpp src/Renderer/Shader.hpp
        src/Renderer/Texture.cpp src/Renderer/Texture.hpp)
set(SCENE_FILES
        src/System/Components.hpp)
set(SERVER_FILES
        src/Server/RenderingServer.cpp src/Server/RenderingServer.hpp
        src/Server/DisplayServer.cpp src/Server/DisplayServer.hpp
        src/Server/PhysicsServer.cpp src/Server/PhysicsServer.hpp)
set(SYSTEM_FILES
        src/System/PlayerSystem.cpp src/System/PlayerSystem.hpp
        src/System/SceneSystem.cpp src/System/SceneSystem.hpp
        src/System/GraphicsSystem.cpp src/System/GraphicsSystem.hpp)
set(RESOURCE_FILES
        src/Resource/ResourceManager.cpp src/Resource/ResourceManager.hpp)
set(BOX2D_PLATFORM_FILES
        src/Platform/Box2D/Box2DPhysicsServer.cpp)
set(GLFW_PLATFORM_FILES
        src/Platform/GLFW/GLFWCallbacks.hpp src/Platform/GLFW/GLFWCallbacks.cpp
        src/Platform/GLFW/GLFWDisplayServer.cpp)
set(GL3_PLATFORM_FILES
        src/Platform/GL3/GL3Shader.cpp src/Platform/GL3/GL3Shader.hpp
        src/Platform/GL3/GL3VertexArray.cpp src/Platform/GL3/GL3VertexArray.hpp
        src/Platform/GL3/GL3Texture.cpp src/Platform/GL3/GL3Texture.hpp
        src/Platform/GL3/GL3RenderingServer.cpp)
set(GLAD_FILES
        thirdparty/glad/glad.c thirdparty/glad/glad.h thirdparty/glad/khrplatform.h)
set(IMGUI_FILES
        thirdparty/imgui/imconfig.h thirdparty/imgui/imgui.cpp thirdparty/imgui/imgui.h
        thirdparty/imgui/imgui_demo.cpp thirdparty/imgui/imgui_draw.cpp thirdparty/imgui/imgui_internal.h
        thirdparty/imgui/imgui_tables.cpp thirdparty/imgui/imgui_widgets.cpp
        thirdparty/imgui/imstb_rectpack.h thirdparty/imgui/imstb_textedit.h thirdparty/imgui/imstb_truetype.h
        thirdparty/imgui/backends/imgui_impl_glfw.h thirdparty/imgui/backends/imgui_impl_glfw.cpp
        thirdparty/imgui/backends/imgui_impl_opengl3.h thirdparty/imgui/backends/imgui_impl_opengl3.cpp)
add_executable(farming_game
        src/Main.cpp
        ${CORE_FILES} ${INPUT_FILES} ${RENDERER_FILES} ${SCENE_FILES} ${SERVER_FILES} ${SYSTEM_FILES} ${RESOURCE_FILES}
        ${BOX2D_PLATFORM_FILES} ${GLFW_PLATFORM_FILES} ${GL3_PLATFORM_FILES}
        ${GLAD_FILES} ${IMGUI_FILES})
target_include_directories(farming_game PUBLIC
        src/
        thirdparty thirdparty/stb thirdparty/imgui)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw)
target_link_libraries(farming_game glfw)

add_subdirectory(thirdparty/glm)
target_link_libraries(farming_game glm::glm)

add_subdirectory(thirdparty/entt)
target_link_libraries(farming_game EnTT::EnTT)

set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/box2d)
target_link_libraries(farming_game box2d)

add_subdirectory(thirdparty/json)
target_link_libraries(farming_game nlohmann_json)