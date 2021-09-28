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
