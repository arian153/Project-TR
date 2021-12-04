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
#include <vector>
#include <d3d11.h>

namespace GAM400
{
    class TextureCommon;

    class TextureArrayDX11
    {
    public:
        TextureArrayDX11();
        ~TextureArrayDX11();

        ID3D11ShaderResourceView**       Data();
        ID3D11ShaderResourceView* const* Data() const;

    protected:
        std::vector<ID3D11ShaderResourceView*> m_textures;
        ID3D11DeviceContext*                   m_device_context = nullptr;
        TextureCommon*                         m_front          = nullptr;
    };
}
