//
// Created by wesley on 23/04/22.
//

#ifndef FARMING_GAME_GL3TEXTURE_HPP
#define FARMING_GAME_GL3TEXTURE_HPP

#include "Renderer/Texture.hpp"

#include <glad/glad.h>

class GL3Texture : public Texture {
public:
    GL3Texture() = default;
    ~GL3Texture() override = default;

    void create() override;
    void bind(int32_t slot) override;
    void set_data(int32_t width, int32_t height, void* pixels) override;
    void release() override;

private:
    GLuint m_Handle = 0;

};


#endif //FARMING_GAME_GL3TEXTURE_HPP
