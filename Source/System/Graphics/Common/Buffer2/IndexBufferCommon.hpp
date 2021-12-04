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
#include IncludeIndexBufferAPI
#include <vector>

#include "../../../Core/Utility/CoreDef.hpp"

namespace GAM400
{
    class RendererCommon;

    class IndexBufferCommon : public IndexBufferAPI
    {
    public:
        IndexBufferCommon();
        ~IndexBufferCommon();

        bool Init(RendererCommon* renderer, const std::vector<U32>& indices);
        void Bind(U32 offset) const;
        void Draw() const;
        void Draw(U32 instance_count) const;
        void Shutdown();
    private:
        U32 m_indices_count = 0;
    };
}
