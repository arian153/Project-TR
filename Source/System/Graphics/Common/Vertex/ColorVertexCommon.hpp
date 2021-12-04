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
#include "../../GraphicsAPI.hpp"
#include IncludeColorVertexAPI


namespace GAM400
{
    class Vector3;
    class Color;

    class ColorVertexCommon : public ColorVertexAPI
    {
    public:
        ColorVertexCommon();
        ColorVertexCommon(const Vector3& position, const Color& color);

        Vector3 GetPosition() const;
        Color   GetColor() const;

    public:
    };
}
