#pragma once
#include "../Resource.hpp"

namespace GAM400
{
    class RendererCommon;
    class TextureCommon;

    class TextureResource final : public Resource
    {
    public:
        explicit TextureResource(const std::wstring& path);
        ~TextureResource();

        void Initialize() override;
        void Shutdown() override;

        TextureCommon* GetTexture() const;

        void SetRenderer(RendererCommon* renderer);


    private:
        RendererCommon* m_renderer = nullptr;
        TextureCommon*  m_texture  = nullptr;
    };
}
