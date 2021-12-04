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
#include <vector>

#include "../../Core/Utility/CoreDef.hpp"
#include "../../Math/Algebra/Matrix44.hpp"
#include "../../Math/Algebra/Vector3.hpp"
#include "../../Math/Structure/Transform.hpp"
#include "../../Math/Utility/MathDef.hpp"

namespace GAM400
{
    class SkyComponent;
    class Camera;
    class TextureCommon;
    class RendererCommon;
    class VertexBufferCommon;
    class IndexBufferCommon;

    class CubeMapSky
    {
    public:
        CubeMapSky();
        ~CubeMapSky();

        void Initialize();
        void Update(Real dt);
        void Shutdown();

        void Bind() const;
        void Draw() const;

        void GenerateSkySphere();
        void GenerateSkyBox();
        void SetCamera(Camera* camera);
        void SetRenderer(RendererCommon* renderer);
        void SetTexture(TextureCommon* texture);
        void CreateBuffer();

        Matrix44 GetModelMatrix() const;

    private:
        friend class SkyComponent;

    private:
        SkyComponent*       m_component     = nullptr;
        RendererCommon*     m_renderer      = nullptr;
        VertexBufferCommon* m_vertex_buffer = nullptr;
        IndexBufferCommon*  m_index_buffer  = nullptr;
        TextureCommon*      m_texture       = nullptr;
        Camera*             m_camera        = nullptr;

        Transform m_transform;
        float     m_radius = 50.0f;
        int       m_type   = 1;

        std::vector<U32>     m_indices;
        std::vector<Vector3> m_vertices;
    };
}
