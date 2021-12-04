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
#include IncludeInstanceBufferAPI
#include "../../../Core/Utility/CoreDef.hpp"
#include <vector>

#include "ConstantBufferData.hpp"
#include "../Vertex/VertexCommon.hpp"
#include "../Vertex/ColorVertexCommon.hpp"
#include "../Vertex/InstanceDataCommon.hpp"
#include "../Vertex/TextureVertexCommon.hpp"

namespace GAM400
{
    class RendererCommon;

    class InstanceBufferCommon : public InstanceBufferAPI
    {
    public:
        InstanceBufferCommon();
        ~InstanceBufferCommon();

        bool Init(RendererCommon* renderer, const std::vector<InstanceBufferData>& instances);
        void Update(const std::vector<InstanceBufferData>& instances) const;
        void Shutdown();
    private:
    };
}
