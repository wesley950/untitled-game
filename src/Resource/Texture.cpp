//
// Created by wesley on 07/05/22.
//

#include "Texture.hpp"
#include "Server/RenderingServer.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture() {
    static int pixels[] = {
            (int)0xffff00ff, 0x0, (int)0xffff00ff, 0x0
    };

    // Create texture in the rendering server
    m_Handle = RenderingServer::create_texture();
    m_Width = m_Height = 2;
    // Set the pixels to something default
    RenderingServer::set_texture_data(m_Handle, 2, 2, (void*)pixels);
}

Texture::Texture(const std::string& path) {
    int width, height, channels;
    auto pixels = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (pixels != NULL) {
        // TODO: error checking and logging
        m_Handle = RenderingServer::create_texture();
        m_Width = width;
        m_Height = height;
        m_Path = path;
        RenderingServer::set_texture_data(m_Handle, width, height, (void*)pixels);
        stbi_image_free(pixels);
    }
}

Texture::~Texture() {
    if (m_Handle) {
        release();
    }
}

void Texture::set(int32_t width, int32_t height, void* pixels) {
    m_Width = width;
    m_Height = height;
    RenderingServer::set_texture_data(m_Handle, width, height, (void*)pixels);
}

void Texture::release() {
    RenderingServer::destroy_texture(m_Handle);
    m_Handle = m_Width = m_Height = 0;
    m_Path = "";
}
