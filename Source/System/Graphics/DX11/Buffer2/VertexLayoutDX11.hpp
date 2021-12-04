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
#include "../../../Core/Utility/CoreDef.hpp"
#include "../../DataType/VertexAttributeDef.hpp"

namespace GAM400
{
    class VertexAttributeDX11
    {
    public:
        VertexAttributeDX11()  = default;
        ~VertexAttributeDX11() = default;

    public:
        std::string    sem_name   = "";
        U32            sem_idx    = 0;
        eInputSlotType slot_type  = eInputSlotType::VERTEX_DATA;
        U32            input_slot = 0;
        U32            step_rate  = 0;
    };

    class VertexLayoutDX11
    {
    public:
        VertexLayoutDX11();
        ~VertexLayoutDX11();

        void PushDX11(eAttributeType type, U32 count, const std::string& semantic_name, U32 semantic_idx);
        void PushDX11(eAttributeType type, U32 count, const std::string& semantic_name, U32 semantic_idx, eInputSlotType slot_type, U32 input_slot, U32 step_rate);

    protected:
    };
}
