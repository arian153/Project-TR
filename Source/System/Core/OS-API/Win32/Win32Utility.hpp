#pragma once
#include <string>

namespace GAM400
{
    namespace Win32Util
    {
        std::wstring GetMyDocumentPathW();
        std::string GetMyDocumentPath();

        bool CreateDirectoryPath(const std::string& path);
    }


}
