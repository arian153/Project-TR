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
    enum class eAttributeType : int
    {
        T32,
        R32,
        I32,
        U32
    };

    enum class eInputSlotType : int
    {
        VERTEX_DATA,
        INSTANCE_DATA
    };
}
