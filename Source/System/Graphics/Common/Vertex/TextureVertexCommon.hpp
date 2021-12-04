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
#include "../../../Math/Utility/MathDef.hpp"
#include IncludeTextureVertexAPI

namespace GAM400
{
    class Vector2;
    class Vector3;

    class TextureVertexCommon : public TextureVertexAPI
    {
    public:
        TextureVertexCommon();
        TextureVertexCommon(Real px, Real py, Real pz, Real u, Real v);
        TextureVertexCommon(const Vector3& p, const Vector2& _uv);

        Vector3 GetPosition() const;
        Vector2 GetUV() const;

        void SetPosition(const Vector3& p);
        void SetUV(const Vector2& _uv);

    public:
    };
}
