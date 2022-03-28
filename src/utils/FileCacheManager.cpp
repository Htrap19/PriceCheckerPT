//
// Created by htrap19 on 3/28/22.
//

#include "FileCacheManager.h"
#include <fstream>
#include <filesystem>
#include <iostream>

namespace ps
{
    std::string FileCacheManager::s_TempFolderLocation = ".cache/";

    FileCacheManager::FileCacheManager()
    {
        namespace fs = std::filesystem;
        fs::create_directory(".cache");
    }

    std::string FileCacheManager::Set(const std::string& filename, const std::string& data)
    {
        std::ofstream file(GetRelativePath(filename), std::ios::trunc);
        if (file)
            file << data;

        return data;
    }

    std::string FileCacheManager::Get(const std::string& filename)
    {
        std::ifstream check_file(GetRelativePath(filename));
        std::string data;
        if (check_file)
        {
            check_file >> data;
            return data;
        }

        return "";
    }

    bool FileCacheManager::Check(const std::string& filename)
    {
        std::ifstream check_file(GetRelativePath(filename));
        return check_file.is_open();
    }
}