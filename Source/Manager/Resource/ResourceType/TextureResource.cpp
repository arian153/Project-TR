/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "TextureResource.hpp"
#include "../../../System/Graphics/Common/Texture/TextureCommon.hpp"

namespace GAM400
{
    TextureResource::TextureResource(const std::wstring& path)
        : Resource(path)
    {
        m_type = eResourceType::Texture;
    }

    TextureResource::~TextureResource()
    {
    }

    void TextureResource::Initialize()
    {
        if (m_renderer != nullptr)
        {
            if (m_texture == nullptr)
            {
                m_texture = new TextureCommon();
                m_texture->Initialize(m_renderer, m_file_path_w, m_file_type_w);
                m_b_loaded = true;
            }
        }
    }

    void TextureResource::Shutdown()
    {
        if (m_texture != nullptr)
        {
            m_texture->Shutdown();
            delete m_texture;
            m_texture = nullptr;
        }
        m_b_unloaded = true;
    }

    TextureCommon* TextureResource::GetTexture() const
    {
        return m_texture;
    }

    void TextureResource::SetRenderer(RendererCommon* renderer)
    {
        m_renderer = renderer;
        Initialize();
    }
}
