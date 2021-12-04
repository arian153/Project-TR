/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "TextureAtlasDX11.hpp"
#include "../../Common/Texture/TextureAtlasCommon.hpp"

namespace GAM400
{
    TextureAtlasDX11::TextureAtlasDX11()
    {
    }

    TextureAtlasDX11::~TextureAtlasDX11()
    {
    }

    TextureAtlasCommon::TextureAtlasCommon()
    {
    }

    TextureAtlasCommon::~TextureAtlasCommon()
    {
    }

    Vector4 TextureAtlasCommon::GetUVRect(size_t index)
    {
        return m_fragments.at(index);
    }

    Vector2 TextureAtlasCommon::ConvertUV(const Vector2& uv, size_t index)
    {
        Vector4 rect = m_fragments.at(index);
        return Vector2(rect.x + uv.x * (rect.z - rect.x), rect.y + uv.y * (rect.w - rect.y));
    }
}
