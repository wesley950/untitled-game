//
// Created by wesley on 02/05/22.
//

#include "Profiler.hpp"

void Profiler::clear() {
    m_Results.clear();
}

void Profiler::add_result(const char* name, float elapsed_time) {
    m_Results.push_back({ name, elapsed_time });
}
