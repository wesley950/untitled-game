//
// Created by wesley on 23/04/22.
//

#pragma once

#include <cstdint>

class Texture {
public:
    Texture() = default;
    virtual ~Texture() = default;

    virtual void create() = 0;
    virtual void bind(int32_t slot) = 0;
    virtual void set_data(int32_t width, int32_t height, void* pixels) = 0;
    virtual void release() = 0;

    [[nodiscard]] int32_t get_width() const { return m_Width; }
    [[nodiscard]] int32_t get_height() const { return m_Height; }
    [[nodiscard]] int32_t get_last_bound_slot() const { return m_LastSlot; }

protected:
    int32_t m_Width = 0;
    int32_t m_Height = 0;
    int32_t m_LastSlot = -1;
};

Texture* create_texture();
