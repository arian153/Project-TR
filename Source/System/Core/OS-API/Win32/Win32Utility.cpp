#include "Win32Utility.hpp"
#include <windows.h>
#include <iostream>
#include <shlobj.h>

#include "../../Utility/CoreUtility.hpp"

#pragma comment(lib, "shell32.lib")

namespace GAM400
{
    std::wstring Win32Util::GetMyDocumentPathW()
    {
        WCHAR   my_documents[MAX_PATH];
        HRESULT result = SHGetFolderPath(nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, my_documents);

        if (result == S_OK)
        {
            return std::wstring(my_documents);
        }
        return L"";
    }

    std::string Win32Util::GetMyDocumentPath()
    {
        return ToString(GetMyDocumentPathW());
    }

    bool Win32Util::CreateDirectoryPath(const std::string& path)
    {
        auto w_path = ToWString(path);

        return CreateDirectory(w_path.c_str(), nullptr) || ERROR_ALREADY_EXISTS == GetLastError();
    }
}
