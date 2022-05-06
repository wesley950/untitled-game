//
// Created by wesley on 23/04/22.
//

#include "GL3Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void GL3Texture::bind(int32_t slot) {
    if (!m_Handle)
        create();

    m_LastSlot = slot;

    if (m_LastSlot <= -1 || m_LastSlot >= (GL_TEXTURE31 - GL_TEXTURE0))
        m_LastSlot = 0;
    glActiveTexture(m_LastSlot);
    glBindTexture(GL_TEXTURE_2D, m_Handle);
}

void GL3Texture::set_data(int32_t width, int32_t height, void *pixels) {
    m_Width = width;
    m_Height = height;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

void GL3Texture::release() {
    glDeleteTextures(1, &m_Handle);
    m_Handle = 0;
    m_Width = m_Height = 0;
    m_LastSlot = -1;
}

void GL3Texture::load_from_file(const std::string& path) {
    if (!m_Handle)
        create();

    int width = 0, height = 0, channels = 0;
    auto pixels = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (pixels) {
        set_data(width, height, pixels);
    }
    else {
        std::printf("Could not load texture from \"%s\"...\n", path.c_str());
    }
}

void GL3Texture::create() {
    // temp buffer with a checkerboard texture
    unsigned int initialPixels[] = {
            0xff0000ff, 0xff00ff00, 0xffff0000, 0xffff00ff
    };

    // save the texture for later...
    GLint currentTexture = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);
    glGenTextures(1, &m_Handle);
    glBindTexture(GL_TEXTURE_2D, m_Handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)initialPixels);
    m_Width = 2;
    m_Height = 2;
}

Texture* create_texture() {
    return new GL3Texture();
}
