#pragma once
#include "pch.h"

namespace dat::utils 
{
    class Timer
    {
    public:
        Timer()
        {
            restart();
        }

    public:
        void restart() 
        {
            m_StartTime = high_resolution_clock::now();
        }

        float duration() const
        {
            std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - m_StartTime;
            return std::chrono::duration_cast<microseconds>(duration).count();
        }

    private:
        time_point<std::chrono::high_resolution_clock> m_StartTime;
    };
}