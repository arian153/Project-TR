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
#include <d3d11.h>

#include "../../../Core/Utility/CoreDef.hpp"

namespace GAM400
{
    class InstanceBufferDX11
    {
    public:
        InstanceBufferDX11();
        ~InstanceBufferDX11();

    public:
        ID3D11Buffer* m_instance_buffer = nullptr;
        U32           m_stride          = 0;
    protected:
        ID3D11DeviceContext* m_device_context = nullptr;
        ID3D11Device*        m_device         = nullptr;
    };
}
