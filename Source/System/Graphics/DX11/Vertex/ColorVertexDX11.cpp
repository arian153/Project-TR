/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "ColorVertexDX11.hpp"
#include "../../../Math/Math.hpp"
#include "../../DataType/Color.hpp"
#include "../ConverterDX11.hpp"
#include "../../Common/Vertex/ColorVertexCommon.hpp"

namespace GAM400
{
    ColorVertexDX11::ColorVertexDX11()
        : position(), color()
    {
    }

    ColorVertexDX11::~ColorVertexDX11()
    {
    }

    ColorVertexCommon::ColorVertexCommon()
    {
        position.x = 0.0f;
        position.y = 0.0f;
        position.z = 0.0f;
        color.w    = 1.0f;
        color.x    = 1.0f;
        color.y    = 1.0f;
        color.z    = 1.0f;
    }

    ColorVertexCommon::ColorVertexCommon(const Vector3& _position, const Color& _color)
    {
        position = ConverterDX11::ToXMFloat3(_position);
        color    = ConverterDX11::ToXMFloat4(_color);
    }

    Vector3 ColorVertexCommon::GetPosition() const
    {
        return ConverterDX11::ToVector3(position);
    }

    Color ColorVertexCommon::GetColor() const
    {
        return ConverterDX11::ToColor(color);
    }
}
