/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#pragma once
#include "../../Math/Utility/MathDef.hpp"
#include "CoreDef.hpp"
#include <chrono>

namespace GAM400
{
    class TimeUtility
    {
    public:
        TimeUtility();
        ~TimeUtility();

        Real TotalTime() const;
        Real DeltaTime() const;

        void Reset();
        void Start();
        void Stop();
        void Tick();

        void RecordBegin();
        Real RecordEnd();

        static std::string GetCurrentTimeString();

    private:
        //time data
        std::chrono::time_point<std::chrono::high_resolution_clock> m_base_point;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_prev_point;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_curr_point;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_stop_point;

        std::chrono::time_point<std::chrono::high_resolution_clock> m_begin_point;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_end_point;

        //duration
        std::chrono::duration<R64> m_tick_duration;
        std::chrono::duration<R64> m_paused_duration;

        //others
        R64  m_delta_time = -1.0;
        bool m_b_stopped  = false;
    };
}
