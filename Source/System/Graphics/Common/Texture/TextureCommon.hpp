#pragma once
#include "../../GraphicsAPI.hpp"
#include IncludeTextureAPI
#include <string>

namespace GAM400
{
    class PixelData;
    class RenderTextureBufferCommon;
    class TextTextureBufferCommon;
    class RendererCommon;

    class TextureCommon : public TextureAPI
    {
    public:
        TextureCommon();
        ~TextureCommon();

        bool Initialize(RendererCommon* renderer, const std::wstring& file_path, const std::wstring& file_type);
        bool Initialize(TextTextureBufferCommon* text_buffer);
        bool Initialize(RenderTextureBufferCommon* render_texture_buffer);
        bool InitializeDefault(RendererCommon* renderer);
        bool Initialize(RendererCommon* renderer, PixelData* pixel_data);
        bool Shutdown();
        void Bind() const;

    private:
        friend class TextureArrayCommon;
        bool m_b_created = false;
    };
}
