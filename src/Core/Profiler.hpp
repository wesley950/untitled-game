//
// Created by wesley on 02/05/22.
//

#pragma once

#include <vector>

#include "Timer.hpp"

class Profiler {
private:
    Profiler() = default;
    ~Profiler() = default;

public:
    struct Result {
        const char* m_Name = nullptr;
        float m_ElapsedTime = 0.0f;
    };

    void clear();
    void add_result(const char* name, float elapsed_time);
    const std::vector<Result>& get_results() const { return m_Results; }

    static Profiler* get() {
        static Profiler* s_Instance = new Profiler();
        return s_Instance;
    }

private:
    std::vector<Result> m_Results {};
};

#define PROFILER_SCOPE(name) Timer timer##__LINE__(name, [] (const char* tn, float et) { Profiler::get()->add_result(tn, et); })
#define PROFILER_CLEAR() Profiler::get()->clear()
