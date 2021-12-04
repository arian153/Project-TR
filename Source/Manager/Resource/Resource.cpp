/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "Resource.hpp"

namespace GAM400
{
    Resource::Resource(const std::wstring& path)
        : m_file_path_w(path)
    {
    }

    Resource::~Resource()
    {
    }

    bool Resource::IsLoaded() const
    {
        return m_b_loaded;
    }

    bool Resource::IsUnloaded() const
    {
        return m_b_unloaded;
    }

    std::wstring Resource::WFileName() const
    {
        return m_file_name_w;
    }

    std::wstring Resource::WFilePath() const
    {
        return m_file_path_w;
    }

    std::wstring Resource::WFileType() const
    {
        return m_file_type_w;
    }

    std::string Resource::FileName() const
    {
        return m_file_name_m;
    }

    std::string Resource::FilePath() const
    {
        return m_file_path_m;
    }

    std::string Resource::FileType() const
    {
        return m_file_type_m;
    }
}
