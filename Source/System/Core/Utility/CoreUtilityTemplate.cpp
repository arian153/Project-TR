/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

namespace GAM400
{
    template <typename First, typename... Rest>
    void UnusedParameter(const First& first, const Rest& ... rest)
    {
        first;
        UnusedParameter(rest...);
    }

    template <typename T>
    void UnusedParameter(const T& t)
    {
        t;
    }
}
