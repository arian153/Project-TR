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

namespace GAM400
{
    class FrameUtility
    {
    public:
        FrameUtility();
        ~FrameUtility();

        void CalculateFrameStatus(Real total_time);
        Real GetFramePerSecond() const;
        Real GetMillisecondPerFrame() const;
        Real GetSecondPerFrame() const;

    private:
        size_t m_frame_count  = 0;
        Real   m_elapsed_time = 0.0f;
        Real   m_curr_fps     = 0.0f;
        Real   m_curr_mspf    = 0.0f;
    };
}
