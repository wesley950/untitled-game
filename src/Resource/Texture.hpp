//
// Created by wesley on 07/05/22.
//

#pragma once

#include <string>
#include <cstdint>

class Texture {
public:
    Texture();
    Texture(const std::string& path);
    ~Texture();

    void set(int32_t width, int32_t height, void* pixels);
    void release();

    const int32_t get_width() const { return m_Width; }
    const int32_t get_height() const { return m_Height; }
    const int32_t get_handle() const { return m_Handle; }
    const std::string& get_path() const { return m_Path; }

private:
    std::string m_Path {};
    int32_t m_Width = 0, m_Height = 0;
    int32_t m_Handle = 0;
};
