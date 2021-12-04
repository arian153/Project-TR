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
#include "CoreDef.hpp"

namespace GAM400
{
    inline constexpr U64 Byte(U64 n)
    {
        return n;
    }

    inline constexpr U64 KB(U64 n)
    {
        return n * 1000LL;
    }

    inline constexpr U64 MB(U64 n)
    {
        return KB(n) * 1000LL;
    }

    inline constexpr U64 GB(U64 n)
    {
        return MB(n) * 1000LL;
    }

    template<typename T>
    inline String TypeToString()
    {
        return typeid(T).name();
    }

}