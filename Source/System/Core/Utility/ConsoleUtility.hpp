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
#include <iostream>

namespace GAM400
{
    namespace Console
    {
        void CreateConsole();
        void DestroyConsole();
        void ClearConsole();
        void MessageOut(const std::string& output_message);
        void MessageOut(const std::wstring& output_message);

        template <typename First, typename... Rest>
        void ConsoleOut(const First& first, const Rest&...rest)
        {
            std::cout << first << ", ";
            ConsoleOut(rest...);
        }

        template <typename T>
        void ConsoleOut(const T& t)
        {
            std::cout << t;
        }

        inline void ConsoleOut()
        {
        }
    }
}
