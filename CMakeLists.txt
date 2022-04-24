cmake_minimum_required(VERSION 3.22)
project(farming_game)

set(CMAKE_CXX_STANDARD 17)

# Executes the script to "export" the contents of the shader files into a header file
execute_process(COMMAND python3 ${PROJECT_SOURCE_DIR}/tools/generate_shader_headers.py ${PROJECT_BINARY_DIR})

set(CORE_FILES
        src/Core/Application.hpp src/Core/Application.cpp
        src/Core/UUID.cpp src/Core/UUID.hpp
        src/Core/MathUtils.hpp)
set(INPUT_FILES
        src/Input/Input.cpp src/Input/Input.hpp)
set(RENDERER_FILES
        src/Renderer/Renderer.cpp src/Renderer/Renderer.hpp
        src/Renderer/VertexArray.cpp src/Renderer/VertexArray.hpp
        src/Renderer/Shader.cpp src/Renderer/Shader.hpp src/Renderer/Texture.cpp src/Renderer/Texture.hpp)
set(SCENE_FILES
        src/Scene/Components.hpp
        src/Scene/Scene.cpp src/Scene/Scene.hpp
        src/Scene/Scene_Player.cpp src/Scene/Components_Player.hpp)
set(GENERATED_FILES
        ${PROJECT_BINARY_DIR}/src/Generated/GL3/Shaders.hpp)
set(GLFW_PLATFORM_FILES
        src/Platform/GLFW/GLFWApplication.cpp src/Platform/GLFW/GLFWApplication.hpp
        src/Platform/GLFW/GLFWCallbacks.hpp src/Platform/GLFW/GLFWCallbacks.cpp)
set(GL3_PLATFORM_FILES
        src/Platform/GL3/GL3Shader.cpp src/Platform/GL3/GL3Shader.hpp
        src/Platform/GL3/GL3VertexArray.cpp src/Platform/GL3/GL3VertexArray.hpp
        src/Platform/GL3/GL3Texture.cpp src/Platform/GL3/GL3Texture.hpp)
set(GLAD_FILES
        thirdparty/glad/glad.c thirdparty/glad/glad.h thirdparty/glad/khrplatform.h)
add_executable(farming_game
        src/Main.cpp
        ${CORE_FILES} ${INPUT_FILES} ${RENDERER_FILES} ${SCENE_FILES}
        ${GENERATED_FILES}
        ${GLFW_PLATFORM_FILES} ${GL3_PLATFORM_FILES}
        ${GLAD_FILES})
target_include_directories(farming_game PUBLIC src/ ${PROJECT_BINARY_DIR}/src thirdparty)


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