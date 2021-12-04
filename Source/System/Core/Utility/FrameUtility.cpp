/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "FrameUtility.hpp"

namespace GAM400
{
    FrameUtility::FrameUtility()
    {
    }

    FrameUtility::~FrameUtility()
    {
    }

    void FrameUtility::CalculateFrameStatus(Real total_time)
    {
        m_frame_count++;
        // Compute averages over one second period.
        if (total_time - m_elapsed_time >= 1.0f)
        {
            m_curr_fps  = (Real)m_frame_count; // fps = frame count / 1 second
            m_curr_mspf = 1000.0f / m_curr_fps;
            // Reset for next average.
            m_frame_count = 0;
            m_elapsed_time += 1.0f;
        }
    }

    Real FrameUtility::GetFramePerSecond() const
    {
        return m_curr_fps;
    }

    Real FrameUtility::GetMillisecondPerFrame() const
    {
        return m_curr_mspf;
    }

    Real FrameUtility::GetSecondPerFrame() const
    {
        return (1.0f / m_curr_fps);
    }
}
