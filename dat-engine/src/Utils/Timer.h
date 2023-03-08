#pragma once
#include <chrono>

namespace dat
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
            m_StartTime = std::chrono::high_resolution_clock::now();
        }

        long long duration() const
        {
            std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - m_StartTime;
            return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
        }

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
    };
}