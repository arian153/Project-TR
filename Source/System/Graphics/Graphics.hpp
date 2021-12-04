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

#include "RenderSystem.hpp"
#include "DataType/Color.hpp"
#include "DataType/Frustum.hpp"
#include "DataType/MeshData.hpp"
#include "DataType/MatrixData.hpp"
#include "DataType/MeshInfo.hpp"
#include "DataType/Particle.hpp"
#include "DataType/ProjectionType.hpp"
#include "DataType/TopologyDef.hpp"

#include "Element/Camera.hpp"
#include "Element/ParticleEmitter.hpp"
#include "Element/Scene.hpp"

#include "Common/Renderer/RendererCommon.hpp"
#include "Common/Texture/TextureArrayCommon.hpp"
#include "Common/Texture/TextureAtlasCommon.hpp"
#include "Common/Texture/TextureCommon.hpp"

#include "Utility/MatrixManager.hpp"
#include "Utility/MeshGenerator.hpp"
#include "Utility/ParticleSystem.hpp"
#include "Utility/PrimitiveRenderer.hpp"
#include "Utility/RenderTextureGenerator.hpp"
#include "Utility/TextRenderer.hpp"

