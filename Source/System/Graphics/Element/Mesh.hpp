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
#include "../Common/Shader/ShaderType.hpp"
#include "../Common/Texture/TextureArrayCommon.hpp"
#include "../DataType/MaterialData.hpp"

namespace GAM400
{
    class ResourceManager;
    class ConstantBufferCommon;
    struct InstanceBufferData;
    class InstanceBufferCommon;
    class IndexBufferCommon;
    class VertexBufferCommon;
    class Transform;
    class MeshData;
    class RendererCommon;
    class ShaderManagerCommon;

    class Mesh
    {
    public:
        Mesh();
        ~Mesh();

        void Initialize();
        void Shutdown();

        void Bind() const;
        void Draw() const;
        void CreateBuffer();

        void AddInstance(const InstanceBufferData& data);
        void AddInstance(Transform* transform);
        void AddInstance(Transform* transform, const MaterialColor& color);
        void ClearCount(U32 clear_idx = 0);

        void SetModelData(MeshData* data);
        void AddTexture(TextureCommon* texture);
        void ClearTexture();
        void RemoveTexture(TextureCommon* texture);
        void SetRenderer(RendererCommon* renderer);
        void ResizeInstanceBuffer(U32 count);

        void SetMaterialIdentifier(const MaterialIdentifier& material_data);
        void SetSceneID(size_t model_id, size_t material_id);

        std::string GetShaderType() const;

    private:
        friend class MeshComponent;

    private:
        ShaderManagerCommon* m_shader_manager   = nullptr;
        RendererCommon*      m_renderer         = nullptr;
     

        MeshData*          m_mesh_data = nullptr;
        TextureArrayCommon m_textures;

        VertexBufferCommon*   m_vertex_buffer   = nullptr;
        IndexBufferCommon*    m_index_buffer    = nullptr;
        InstanceBufferCommon* m_instance_buffer = nullptr;
        ConstantBufferCommon* m_texture_buffer  = nullptr;
        U32                   m_max_count       = 0;
        U32                   m_instance_count  = 0;

        size_t m_material_id   = (size_t)-1;
        size_t m_model_id      = (size_t)-1;
        int    m_diffuse_type  = -1;
        int    m_specular_type = -1;
        int    m_normal_type   = -1;

        std::string                     m_shader_type = "";
        std::vector<InstanceBufferData> m_instances;
    };
}
