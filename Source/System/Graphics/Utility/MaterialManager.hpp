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
#include <string>
#include <vector>

#include "../DataType/MaterialData.hpp"

namespace GAM400
{
    class MaterialManager
    {
    public:
        MaterialManager();
        ~MaterialManager();

        void Initialize();
        void Shutdown();

        size_t       GetID(const MaterialIdentifier& material);
        MaterialIdentifier GetMaterial(size_t id);

    private:
        std::vector<MaterialIdentifier> m_data;
    };
}
