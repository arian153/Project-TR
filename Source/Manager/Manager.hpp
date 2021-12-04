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

#include "Component/Component.hpp"
#include "Component/ComponentManager.hpp"
#include "Component/EngineComponent/CameraComponent.hpp"
#include "Component/EngineComponent/LightComponent.hpp"
#include "Component/EngineComponent/MeshComponent.hpp"
#include "Component/EngineComponent/ParticleEmitterComponent.hpp"
#include "Component/EngineComponent/TransformComponent.hpp"
#include "Component/GameComponent/LogicComponent.hpp"
#include "Component/ComponentFactory.hpp"
#include "Component/ComponentRegistry.hpp"

#include "Level/Level.hpp"
#include "Level/LevelManager.hpp"

#include "Object/Object.hpp"
#include "Object/ObjectFactory.hpp"
#include "Object/ObjectManager.hpp"

#include "Resource/Resource.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/ResourceType.hpp"
#include "Resource/ResourceType/AudioResource.hpp"
#include "Resource/ResourceType/JsonResource.hpp"
#include "Resource/ResourceType/MeshResource.hpp"
#include "Resource/ResourceType/ShaderResource.hpp"
#include "Resource/ResourceType/TextResource.hpp"
#include "Resource/ResourceType/TextureResource.hpp"
#include "Resource/ResourceType/UndefinedResource.hpp"

#include "Space/Space.hpp"
#include "Space/SpaceManager.hpp"
#include "Space/SubsystemFlag.hpp"

