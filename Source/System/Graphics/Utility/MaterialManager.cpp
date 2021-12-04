/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "MaterialManager.hpp"

namespace GAM400
{
    MaterialManager::MaterialManager()
    {
    }

    MaterialManager::~MaterialManager()
    {
    }

    void MaterialManager::Initialize()
    {
    }

    void MaterialManager::Shutdown()
    {
        m_data.clear();
    }

    size_t MaterialManager::GetID(const MaterialIdentifier& material)
    {
        size_t id      = m_data.size();
        bool   b_found = false;
        for (size_t i = 0; i < id; ++i)
        {
            if (m_data[i] == material)
            {
                b_found = true;
                id      = i;
                break;
            }
        }

        if (b_found == false)
        {
            m_data.push_back(material);
        }
        return id;
    }

    MaterialIdentifier MaterialManager::GetMaterial(size_t id)
    {
        return m_data[id];
    }
}
