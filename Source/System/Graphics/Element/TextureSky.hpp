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
#include "../../Math/Utility/MathDef.hpp"

namespace GAM400
{
    class RendererCommon;
    class VertexBufferCommon;
    class IndexBufferCommon;
    class Camera;
    class TextureCommon;
    class MeshData;

    class TextureSky
    {
    public:
        TextureSky();
        ~TextureSky();

        void Initialize();
        void Update(Real dt);
        void Shutdown();

    private:
        friend class SkyComponent;

    private:
        SkyComponent* m_component     = nullptr;
        RendererCommon*          m_renderer      = nullptr;
        VertexBufferCommon*      m_vertex_buffer = nullptr;
        IndexBufferCommon*       m_index_buffer  = nullptr;
        TextureCommon*           m_texture       = nullptr;
        Camera*                  m_camera        = nullptr;
    };
}
