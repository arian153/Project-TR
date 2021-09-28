#pragma once
#include <directxmath.h>

namespace GAM400
{
    class ColorVertexDX11
    {
    public:
        ColorVertexDX11();
        ~ColorVertexDX11();

    public:
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT4 color;
    };
}
