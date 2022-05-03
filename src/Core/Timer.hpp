//
// Created by wesley on 02/05/22.
//

#pragma once

#include <vector>
#include <chrono>

template<typename TimeOutFunc>
class Timer {
public:
    Timer() = delete;
    Timer(const char* name, TimeOutFunc&& tof) : m_Name(name), m_TimeOutFunc(tof) {
        m_TimeOnStart = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = (now - m_TimeOnStart);
        float elapsed_time = duration.count();
        m_TimeOutFunc(m_Name, elapsed_time);
    }

private:
    const char* m_Name = nullptr;
    TimeOutFunc m_TimeOutFunc;

    std::chrono::time_point<std::chrono::high_resolution_clock> m_TimeOnStart {};
};
