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
#include "../Resource.hpp"
#include "../../../System/Graphics/DataType/MeshData.hpp"

namespace GAM400
{
    enum class eMeshType : size_t
    {
        Invalid
      , CustomTXT
      , WaveFrontOBJ
    };

    enum class eOBJFaceType
    {
        Point,
        PointTexture,
        PointNormal,
        PointTextureNormal
    };

    class MeshResource final : public Resource
    {
    public:
        explicit MeshResource(const std::wstring& path);
        ~MeshResource();

        void Initialize() override;
        void Shutdown() override;

        void LoadWaveFrontOBJ(std::ifstream& file);
        void LoadGeneralOBJ(std::ifstream& file);
        void LoadOBJOnlyPos(std::ifstream& file);
        void LoadCustomTXT(std::ifstream& file);
        void CheckMeshType();

        MeshData* GetMeshData() ;

    private:
        eMeshType m_mesh_type = eMeshType::Invalid;
        MeshData  m_mesh_data;
    };
}
