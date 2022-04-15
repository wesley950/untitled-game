//
// Created by wesley on 15/04/22.
//

#include "UUID.hpp"

UUID::UUID() {
    static std::random_device rd {};
    static std::mt19937_64 rng { rd() };
    static std::uniform_int_distribution<int64_t> uid {};

    this->m_Value = uid(rng);
}

UUID::UUID(const UUID &other) {
    this->m_Value = other.m_Value;
}
