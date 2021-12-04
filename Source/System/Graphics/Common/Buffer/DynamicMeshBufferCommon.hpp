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
#include IncludeDynamicMeshBufferAPI
#include <vector>

#include "../../../Core/Utility/CoreDef.hpp"
#include "../Vertex/VertexCommon.hpp"
#include "../Vertex/ColorVertexCommon.hpp"
#include "../Vertex/TextureVertexCommon.hpp"

namespace GAM400
{
    class RendererCommon;

    class DynamicMeshBufferCommon : public DynamicMeshBufferAPI
    {
    public:
        DynamicMeshBufferCommon();
        ~DynamicMeshBufferCommon();

        void Render(U32 stride, U32 offset) const;
        void Shutdown();

        bool BuildBuffer(RendererCommon* renderer, const std::vector<ColorVertexCommon>& vertices, const std::vector<U32>& indices);
        bool BuildBuffer(RendererCommon* renderer, const std::vector<TextureVertexCommon>& vertices, const std::vector<U32>& indices);
        bool BuildBuffer(RendererCommon* renderer, const std::vector<VertexCommon>& vertices, const std::vector<U32>& indices);

        void UpdateVertexBuffer(const std::vector<ColorVertexCommon>& vertices) const;
        void UpdateVertexBuffer(const std::vector<TextureVertexCommon>& vertices) const;
        void UpdateVertexBuffer(const std::vector<VertexCommon>& vertices) const;

    private:
    };
}
