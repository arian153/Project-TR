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

namespace GAM400
{
    enum class eSubsystemFlag : size_t
    {
        None = 0x00
      , ComponentManager = 0x1
      , ObjectManager = 0x2
      , Scene = 0x4
      , World = 0x8
      , Logic = 0x16
    };

    constexpr eSubsystemFlag operator^(eSubsystemFlag a, eSubsystemFlag b)
    {
        return static_cast<eSubsystemFlag>(static_cast<size_t>(a) ^ static_cast<size_t>(b));
    }

    constexpr eSubsystemFlag operator~(eSubsystemFlag flag)
    {
        return static_cast<eSubsystemFlag>(~static_cast<size_t>(flag));
    }

    constexpr eSubsystemFlag operator&(eSubsystemFlag a, eSubsystemFlag b)
    {
        return static_cast<eSubsystemFlag>(static_cast<size_t>(a) & static_cast<size_t>(b));
    }

    constexpr eSubsystemFlag operator|(eSubsystemFlag a, eSubsystemFlag b)
    {
        return static_cast<eSubsystemFlag>(static_cast<size_t>(a) | static_cast<size_t>(b));
    }

    inline eSubsystemFlag& operator&=(eSubsystemFlag& a, eSubsystemFlag b)
    {
        a = a & b;
        return a;
    }

    inline eSubsystemFlag& operator|=(eSubsystemFlag& a, eSubsystemFlag b)
    {
        a = a | b;
        return a;
    }

    inline eSubsystemFlag& operator^=(eSubsystemFlag& a, eSubsystemFlag b)
    {
        a = a ^ b;
        return a;
    }

    inline bool HasFlag(eSubsystemFlag a, eSubsystemFlag b)
    {
        return (a & b) == b;
    }
}
