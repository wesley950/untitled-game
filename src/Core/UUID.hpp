//
// Created by wesley on 15/04/22.
//

#ifndef UNTITLED_UUID_HPP
#define UNTITLED_UUID_HPP

#include <random>
#include <cstdint>

class UUID {
public:
    UUID();
    UUID(const UUID& other);

    [[nodiscard]] int64_t get() const { return m_Value; }

private:
    int64_t m_Value;
};


#endif //UNTITLED_UUID_HPP
