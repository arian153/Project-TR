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
#include <vector>

#include "../Resource.hpp"
#include "../../../System/Core/Utility/CoreDef.hpp"
#include "../../../System/Math/Utility/MathDef.hpp"

namespace GAM400
{
    class PixelData
    {
    public:
        struct PixelRGB
        {
            PixelRGB();
            explicit PixelRGB(Real value);
            PixelRGB(Real red, Real green, Real blue);

        public:
            Real r, g, b;
        };

        PixelData();
        PixelData(const U32& width, const U32& height);
        ~PixelData();

        void ToRGBA8(std::vector<U32>& rgba) const;
        U32 ToRGBA8(size_t idx) const;

        U32  w, h;
        PixelRGB* pixels;
    };

    class TextResource final : public Resource
    {
    public:
        explicit TextResource(const std::wstring& path);
        ~TextResource();

        void Initialize() override;
        void Shutdown() override;
        bool LoadText();

        std::wstring GetText() const;

        bool        LoadPPM();
        static bool SavePPM(PixelData* data, const std::string& new_path);

        PixelData* GetPixelData() const;

    private:
        std::wstring m_text       = L"";
        PixelData*   m_pixel_data = nullptr;
    };
}
