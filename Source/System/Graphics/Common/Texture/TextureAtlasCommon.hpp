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
#include IncludeTextureAtlasAPI
#include "../../../Math/Algebra/Vector4.hpp"
#include "../../../Math/Algebra/Vector2.hpp"
#include <vector>

namespace GAM400
{
    class TextureAtlasCommon : public TextureAtlasAPI
    {
    public:
        TextureAtlasCommon();
        ~TextureAtlasCommon();

        Vector4 GetUVRect(size_t index);

        Vector2 ConvertUV(const Vector2& uv, size_t index);

    private:
        std::vector<Vector4> m_fragments;
    };
}
