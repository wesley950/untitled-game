//
// Created by wesley on 15/04/22.
//

#pragma once

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
