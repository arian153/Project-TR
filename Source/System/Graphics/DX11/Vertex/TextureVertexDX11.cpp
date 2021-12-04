/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "TextureVertexDX11.hpp"
#include "../../Common/Vertex/TextureVertexCommon.hpp"
#include "../../../Math/Algebra/Vector2.hpp"
#include "../../../Math/Algebra/Vector3.hpp"
#include "../ConverterDX11.hpp"

namespace GAM400
{
    TextureVertexDX11::TextureVertexDX11()
        : position(), uv()
    {
    }

    TextureVertexDX11::~TextureVertexDX11()
    {
    }

    TextureVertexCommon::TextureVertexCommon()
    {
    }

    TextureVertexCommon::TextureVertexCommon(Real px, Real py, Real pz, Real u, Real v)
    {
        position.x = px;
        position.y = py;
        position.z = pz;
        uv.x = u;
        uv.y = v;
    }

    TextureVertexCommon::TextureVertexCommon(const Vector3& p, const Vector2& _uv)
    {
        position = ConverterDX11::ToXMFloat3(p);
        uv = ConverterDX11::ToXMFloat2(_uv);
    }

    Vector3 TextureVertexCommon::GetPosition() const
    {
        return ConverterDX11::ToVector3(position);
    }

    Vector2 TextureVertexCommon::GetUV() const
    {
        return Vector2(uv.x, uv.y);
    }

    void TextureVertexCommon::SetPosition(const Vector3& p)
    {
        position = ConverterDX11::ToXMFloat3(p);
    }

    void TextureVertexCommon::SetUV(const Vector2& _uv)
    {
        uv = ConverterDX11::ToXMFloat2(_uv);
    }
}
