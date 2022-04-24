//
// Created by wesley on 23/04/22.
//

#include "GL3Texture.hpp"

void GL3Texture::bind(int32_t slot) {
    if (!m_Handle)
        create();

    m_LastSlot = slot;

    if (m_LastSlot <= -1 || m_LastSlot >= (GL_TEXTURE31 - GL_TEXTURE0))
        m_LastSlot = 0;
    glActiveTexture(GL_TEXTURE0 + m_LastSlot);
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

void GL3Texture::create() {
    // temp buffer with a checkerboard texture
    unsigned int initialPixels[] = {
            0x0, 0xff00ffff,
            0xff00ffff, 0x0
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
    // ...rebind previous texture
    if (currentTexture)
        glBindTexture(GL_TEXTURE_2D, currentTexture);
}

Texture* create_texture() {
    return new GL3Texture();
}
