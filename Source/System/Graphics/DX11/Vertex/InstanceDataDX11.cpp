/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "InstanceDataDX11.hpp"
#include "../../Common/Vertex/InstanceDataCommon.hpp"
#include "../ConverterDX11.hpp"

namespace GAM400
{
    InstanceDataDX11::InstanceDataDX11()
        : world(), color()
    {
    }

    InstanceDataDX11::~InstanceDataDX11()
    {
    }

    InstanceDataCommon::InstanceDataCommon()
    {
    }

    InstanceDataCommon::~InstanceDataCommon()
    {
    }

    InstanceDataCommon::InstanceDataCommon(const Matrix44& w, const Color& c)
    {
        world = ConverterDX11::ToXMFloat4X4(w);
        color = ConverterDX11::ToXMFloat4(c);
    }
}
