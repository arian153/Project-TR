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
#include "../../GraphicsAPI.hpp"
#include IncludeTextureArrayAPI

namespace GAM400
{
    class TextureCommon;

    class TextureArrayCommon : public TextureArrayAPI
    {
    public:
        TextureArrayCommon();
        ~TextureArrayCommon();

        void PushFront(TextureCommon* texture);
        void PushBack(TextureCommon* texture);
        void Erase(TextureCommon* texture);
        void Clear();

        TextureCommon* Front() const;
        size_t         Size() const;
        void           Bind() const;

    private:
    };
}
