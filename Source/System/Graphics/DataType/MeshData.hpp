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
#include "../../Core/Utility/CoreDef.hpp"
#include <vector>

#include "MeshInfo.hpp"
#include "../Common/Vertex/ColorVertexCommon.hpp"
#include "../Common/Vertex/NormalVertexCommon.hpp"
#include "../Common/Vertex/VertexCommon.hpp"
#include "../Common/Vertex/TextureVertexCommon.hpp"

namespace GAM400
{
    class MeshData
    {
    public:
        MeshData();
        ~MeshData();

        void Convert(std::vector<ColorVertexCommon>& new_vertices, const Color& color);
        void Convert(std::vector<TextureVertexCommon>& new_vertices);
        void Convert(std::vector<NormalVertexCommon>& new_vertices);

        void    Normalize(Vector3& min, Vector3& max);
        Vector3 GetFaceNormal(U32 a, U32 b, U32 c);

        MeshData& operator= (const MeshData& rhs);
        MeshData(const MeshData& rhs);

    public:
        std::vector<VertexCommon>      vertices;
        std::vector<GeometryFaceIndex> faces;
        std::vector<U32>               indices;
        bool                           b_resource = false;
        U32                            stride     = sizeof(VertexCommon);
    };
}
