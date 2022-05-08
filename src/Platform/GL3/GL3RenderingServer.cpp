//
// Created by wesley on 03/05/22.
//

#include "Server/RenderingServer.hpp"

#include <unordered_map>

#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// Shaders
static GLuint s_Program = 0;
static GLint s_ProjectionViewMatrixUniform = -1;

// Vertex array
static GLuint s_VertexArray = 0;
static GLuint s_VertexBuffer = 0;
static GLuint s_IndexBuffer = 0;

static GLuint compile_shader(GLenum type, const char* code) {
    GLuint shader = glCreateShader(type);
    GLint result = 0;
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(!result) {
        char info_log[256];
        glGetShaderInfoLog(shader, 256, nullptr, info_log);
        // TODO: log this out
    }
    return shader;
}

static GLuint link_program(GLuint vertex_shader, GLuint fragment_shader) {
    GLuint program = glCreateProgram();
    GLint result = 0;
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result) {
        char info_log[256];
        glGetProgramInfoLog(program, 256, nullptr, info_log);
        // TODO: log this out
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;
}

void RenderingServer::init() {
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    // Compile shaders
    {
        const char* vertex_shader_code = R"(
            #version 330 core

            layout (location = 0) in vec3   aPosition;
            layout (location = 1) in vec4   aColor;
            layout (location = 2) in vec2   aTextureCoordinates;
            layout (location = 3) in float  aTextureSlot;

            out vec4    vColor;
            out vec2    vTextureCoordinates;
            out float   vTextureSlot;

            uniform mat4 uProjectionView;

            void main() {
                gl_Position = uProjectionView * vec4(aPosition, 1);

                vColor = aColor;
                vTextureCoordinates = aTextureCoordinates;
                vTextureSlot = aTextureSlot;
            }
        )";
        const char* fragment_shader_code = R"(
            #version 330 core

            uniform sampler2D uTextureBindings[32];

            in vec4     vColor;
            in vec2     vTextureCoordinates;
            in float    vTextureSlot;

            out vec4 oColor;

            void main() {
                oColor = vColor;

                int texture_slot = int(vTextureSlot);
                switch (texture_slot) {
                    case 1:
                    oColor *= texture(uTextureBindings[0], vTextureCoordinates);
                    break;

                    case 2:
                    oColor *= texture(uTextureBindings[1], vTextureCoordinates);
                    break;

                    case 3:
                    oColor *= texture(uTextureBindings[2], vTextureCoordinates);
                    break;

                    case 4:
                    oColor *= texture(uTextureBindings[3], vTextureCoordinates);
                    break;

                    case 5:
                    oColor *= texture(uTextureBindings[4], vTextureCoordinates);
                    break;

                    case 6:
                    oColor *= texture(uTextureBindings[5], vTextureCoordinates);
                    break;

                    case 7:
                    oColor *= texture(uTextureBindings[6], vTextureCoordinates);
                    break;

                    case 8:
                    oColor *= texture(uTextureBindings[7], vTextureCoordinates);
                    break;

                    case 9:
                    oColor *= texture(uTextureBindings[8], vTextureCoordinates);
                    break;

                    case 10:
                    oColor *= texture(uTextureBindings[9], vTextureCoordinates);
                    break;

                    case 11:
                    oColor *= texture(uTextureBindings[10], vTextureCoordinates);
                    break;

                    case 12:
                    oColor *= texture(uTextureBindings[11], vTextureCoordinates);
                    break;

                    case 13:
                    oColor *= texture(uTextureBindings[12], vTextureCoordinates);
                    break;

                    case 14:
                    oColor *= texture(uTextureBindings[13], vTextureCoordinates);
                    break;

                    case 15:
                    oColor *= texture(uTextureBindings[14], vTextureCoordinates);
                    break;

                    case 16:
                    oColor *= texture(uTextureBindings[15], vTextureCoordinates);
                    break;

                    case 17:
                    oColor *= texture(uTextureBindings[16], vTextureCoordinates);
                    break;

                    case 18:
                    oColor *= texture(uTextureBindings[17], vTextureCoordinates);
                    break;

                    case 19:
                    oColor *= texture(uTextureBindings[18], vTextureCoordinates);
                    break;

                    case 20:
                    oColor *= texture(uTextureBindings[19], vTextureCoordinates);
                    break;

                    case 21:
                    oColor *= texture(uTextureBindings[20], vTextureCoordinates);
                    break;

                    case 22:
                    oColor *= texture(uTextureBindings[21], vTextureCoordinates);
                    break;

                    case 23:
                    oColor *= texture(uTextureBindings[22], vTextureCoordinates);
                    break;

                    case 24:
                    oColor *= texture(uTextureBindings[23], vTextureCoordinates);
                    break;

                    case 25:
                    oColor *= texture(uTextureBindings[24], vTextureCoordinates);
                    break;

                    case 26:
                    oColor *= texture(uTextureBindings[25], vTextureCoordinates);
                    break;

                    case 27:
                    oColor *= texture(uTextureBindings[26], vTextureCoordinates);
                    break;

                    case 28:
                    oColor *= texture(uTextureBindings[27], vTextureCoordinates);
                    break;

                    case 29:
                    oColor *= texture(uTextureBindings[28], vTextureCoordinates);
                    break;

                    case 30:
                    oColor *= texture(uTextureBindings[29], vTextureCoordinates);
                    break;

                    case 31:
                    oColor *= texture(uTextureBindings[30], vTextureCoordinates);
                    break;

                    case 32:
                    oColor *= texture(uTextureBindings[31], vTextureCoordinates);
                    break;
                }
            }
        )";

        GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_code);
        GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_code);
        s_Program = link_program(vertex_shader, fragment_shader);
        glUseProgram(s_Program);
        s_ProjectionViewMatrixUniform = glGetUniformLocation(s_Program, "uProjectionView");
    }

    // Create vertex array
    {
        glGenVertexArrays(1, &s_VertexArray);
        glGenBuffers(1, &s_VertexBuffer);
        glGenBuffers(1, &s_IndexBuffer);

        glBindVertexArray(s_VertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, s_VertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_IndexBuffer);
    }
}

void RenderingServer::flush() {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(s_Program);

    // Calculate projection-view matrix and upload to GPU
    {
        float half_width = (s_ViewportSize.x / s_ViewportZoom) / 2.0f;
        float half_height = (s_ViewportSize.y / s_ViewportZoom) / 2.0f;
        s_ProjectionViewMatrix = glm::ortho(-half_width, half_width, half_height, -half_height);
        s_ProjectionViewMatrix = glm::translate(s_ProjectionViewMatrix, glm::vec3(-s_ViewportPosition.x, -s_ViewportPosition.y, 0.0f));
        glUniformMatrix4fv(s_ProjectionViewMatrixUniform, 1, GL_FALSE, glm::value_ptr(s_ProjectionViewMatrix));
    }

    // Upload vertex and index data to GPU
    {
        glBindBuffer(GL_ARRAY_BUFFER, s_VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * s_VertexData.size(), s_VertexData.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * s_IndexData.size(), s_IndexData.data(), GL_STATIC_DRAW);
    }

    // Upload texture slots to shader
    {
        for (int i = 0;i < s_TextureSlots.size();i++) {
            std::string uniform_name = std::string("uTextureBindings[") + std::to_string(i) + std::string("]");
            GLint uniform_location = glGetUniformLocation(s_Program, uniform_name.c_str());
            glUniform1i(uniform_location, s_TextureSlots.at(i));
        }
    }

    // Set vertex attribute pointers
    {
        // Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, aPosition));

        // Color
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, aColor));

        // Texture Coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, aTextureCoordinates));

        // Texture Slot
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, aTextureSlot));
    }

    // Enable blending
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    // Finally draw
    {
        glDrawElements(GL_TRIANGLES, s_IndexData.size(), GL_UNSIGNED_INT, (const void*)0);
    }

    // Cleanup
    {
        s_VertexData.clear();
        s_IndexData.clear();
        s_BaseIndex = 0;
        s_TextureSlots.clear();
    }
}

void RenderingServer::shutdown() {
    // Delete vertex array
    {
        glDeleteBuffers(1, &s_IndexBuffer);
        glDeleteBuffers(1, &s_VertexBuffer);
        glDeleteVertexArrays(1, &s_VertexArray);
        s_IndexBuffer = s_VertexBuffer = s_VertexArray = 0;
    }

    // Delete program
    {
        glDeleteProgram(s_Program);
        s_Program = 0;
        s_ProjectionViewMatrixUniform = -1;
    }
}

void RenderingServer::submit_quad(const glm::mat4& transform,
                                  const glm::vec2& size, const glm::vec2& center, const glm::vec4& color,
                                  const glm::vec2& uv1, const glm::vec2& uv2, int32_t texture_handle) {
    static const int NULL_TEXTURE = 0;

    glm::vec3 offset(
        -(size.x * center.x),
        -(size.y * center.y),
        0.0f
    );

    float texture_slot_attribute = (float)NULL_TEXTURE;

    if (texture_handle) {
        int32_t bound_slot = NULL_TEXTURE;

        // Check if texture id is not on the batch already
        for (int i = 0;i < s_TextureSlots.size();i++) {
            // If it is, use the slot it was bound at as the vertex attribute
            if (s_TextureSlots.at(i) == texture_handle) {
                bound_slot = i;
                break;
            }
        }

        // Otherwise push it to the array and use the index of the last element
        // then bind the texture to the slot
        if (bound_slot == NULL_TEXTURE) {
            bound_slot = s_TextureSlots.size();
            s_TextureSlots.push_back(bound_slot);
            bind_texture(texture_handle, bound_slot);
        }

        // Convert the bound slot so it makes sense in the vertex data
        texture_slot_attribute = (float)(bound_slot+1);
    }

    Vertex vertices[] = {
            {
                    offset,
                    color, { uv1.x, uv1.y }, texture_slot_attribute
            },
            {
                    offset + glm::vec3(size.x, 0.0f, 0.0f),
                    color, { uv2.x, uv1.y }, texture_slot_attribute
            },
            {
                    offset + glm::vec3(size, 0.0f),
                    color, { uv2.x, uv2.y }, texture_slot_attribute
            },
            {
                    offset + glm::vec3(0.0f, size.y, 0.0f),
                    color, { uv1.x, uv2.y }, texture_slot_attribute
            }
    };

    for (auto& vertex : vertices) {
        glm::vec4 temp = transform * glm::vec4(vertex.aPosition, 1.0f);
        vertex.aPosition.x = temp.x;
        vertex.aPosition.y = temp.y;
        s_VertexData.push_back(vertex);
    }

    s_IndexData.push_back(s_BaseIndex + 0);
    s_IndexData.push_back(s_BaseIndex + 1);
    s_IndexData.push_back(s_BaseIndex + 2);
    s_IndexData.push_back(s_BaseIndex + 0);
    s_IndexData.push_back(s_BaseIndex + 2);
    s_IndexData.push_back(s_BaseIndex + 3);
    s_BaseIndex += 4;
}

void RenderingServer::bind_texture(int32_t texture_handle, int32_t slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture_handle);
}

static std::unordered_map<int32_t, GLuint> s_TextureObjects {};

int32_t RenderingServer::create_texture() {
    int32_t texture_handle = ++s_CreatedTextures;
    GLuint texture_object = 0;

    glGenTextures(1, &texture_object);
    glBindTexture(GL_TEXTURE_2D, texture_object);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    s_TextureObjects[texture_handle] = texture_object;
    return texture_handle;
}

void RenderingServer::set_texture_data(int32_t texture_handle, int32_t width, int32_t height, void* pixels) {
    GLuint texture_object = s_TextureObjects.at(texture_handle);
    glBindTexture(GL_TEXTURE_2D, texture_object);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderingServer::destroy_texture(int32_t texture_handle) {
    GLuint texture_object = s_TextureObjects.at(texture_handle);
    glDeleteTextures(1, &texture_object);
    s_TextureObjects.erase(texture_handle);
}
