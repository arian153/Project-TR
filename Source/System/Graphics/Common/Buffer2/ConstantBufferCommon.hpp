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
#include IncludeConstantBufferAPI

#include "../../../Core/Utility/CoreDef.hpp"
#include "../../DataType/BufferBindType.hpp"

namespace GAM400
{
    struct MultipleLightsBufferData;
    struct TextureBufferData;
    enum class eBindingStage;
    struct ColorBufferData;
    struct CameraBufferData;
    struct GammaBufferData;
    struct LightBufferData;
    struct MatrixBufferData;
    struct MatrixBufferDataInstancing;
    struct MaterialBufferData;
    class Color;
    class RendererCommon;

    class ConstantBufferCommon : public ConstantBufferAPI
    {
    public:
        ConstantBufferCommon();
        ~ConstantBufferCommon();

        bool Init(RendererCommon* renderer, eBindingStage type, size_t buffer_size, U32 slot);
        void Update(void* data) const;
        void Update(const ColorBufferData& data) const;
        void Update(const CameraBufferData& data) const;
        void Update(const GammaBufferData& data) const;
        void Update(const LightBufferData& data) const;
        void Update(const MatrixBufferData& data) const;
        void Update(const MatrixBufferDataInstancing& data) const;
        void Update(const TextureBufferData& data) const;
        void Update(const MaterialBufferData& data) const;
        void Update(const MultipleLightsBufferData& data) const;

        void* Map() const;
        void  UnMap() const;

        void Bind() const;
        void Shutdown();
    private:
        U32           m_slot  = 0;
        eBindingStage m_stage = eBindingStage::PixelShader;
    };
}
