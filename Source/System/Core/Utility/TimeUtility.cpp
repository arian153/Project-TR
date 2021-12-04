/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "TimeUtility.hpp"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace GAM400
{
    TimeUtility::TimeUtility()
        : m_tick_duration(), m_paused_duration()
    {
        m_curr_point      = std::chrono::high_resolution_clock::now();
        m_base_point      = m_curr_point;
        m_prev_point      = m_curr_point;
        m_begin_point     = m_curr_point;
        m_stop_point      = std::chrono::time_point<std::chrono::high_resolution_clock>();
        m_b_stopped       = false;
        m_paused_duration = std::chrono::duration<R64>::zero();
    }

    TimeUtility::~TimeUtility()
    {
    }

    Real TimeUtility::TotalTime() const
    {
        std::chrono::duration<R64> total_time = m_b_stopped ? m_stop_point - m_base_point : m_curr_point - m_base_point;
        return static_cast<Real>(total_time.count() - m_paused_duration.count());
    }

    Real TimeUtility::DeltaTime() const
    {
        return static_cast<Real>(m_delta_time);
    }

    void TimeUtility::Reset()
    {
        m_curr_point      = std::chrono::high_resolution_clock::now();
        m_base_point      = m_curr_point;
        m_prev_point      = m_curr_point;
        m_stop_point      = std::chrono::time_point<std::chrono::high_resolution_clock>();
        m_b_stopped       = false;
        m_paused_duration = std::chrono::duration<R64>::zero();
    }

    void TimeUtility::Start()
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        if (m_b_stopped == true)
        {
            m_paused_duration += start_time - m_stop_point;
            m_prev_point = start_time;
            m_stop_point = std::chrono::time_point<std::chrono::high_resolution_clock>();
            m_b_stopped  = false;
        }
    }

    void TimeUtility::Stop()
    {
        if (m_b_stopped == false)
        {
            m_stop_point = std::chrono::high_resolution_clock::now();
            m_b_stopped  = true;
        }
    }

    void TimeUtility::Tick()
    {
        if (m_b_stopped == true)
        {
            m_delta_time = 0.0;
            return;
        }
        m_curr_point    = std::chrono::high_resolution_clock::now();
        m_tick_duration = m_curr_point - m_prev_point;
        m_delta_time    = m_tick_duration.count();
        m_delta_time    = m_delta_time > 0.0 ? m_delta_time : 0.0;
        m_prev_point    = m_curr_point;
    }

    void TimeUtility::RecordBegin()
    {
        m_begin_point = std::chrono::high_resolution_clock::now();
    }

    Real TimeUtility::RecordEnd()
    {
        m_end_point   = std::chrono::high_resolution_clock::now();
        auto duration = m_end_point - m_begin_point;
        return std::chrono::duration<Real>(duration).count();
    }

    std::string TimeUtility::GetCurrentTimeString()
    {
        // ISO 8601 without timezone information.
        auto              time = std::time(nullptr);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%F_%T");
        auto s = ss.str();
        std::replace(s.begin(), s.end(), ':', '-');
        return s;
    }
}
