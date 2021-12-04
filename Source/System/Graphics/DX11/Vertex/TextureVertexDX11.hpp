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
#include <directxmath.h>

namespace GAM400
{
    class TextureVertexDX11
    {
    public:
        TextureVertexDX11();
        ~TextureVertexDX11();

    public:
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT2 uv;
    };
}
