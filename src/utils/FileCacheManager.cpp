//
// Created by htrap19 on 3/28/22.
//

#include "FileCacheManager.h"
#include <fstream>
#include <iostream>

namespace PC
{
    fs::path FileCacheManager::s_CacheFolder = ".cache/";

    void FileCacheManager::Init()
    {
        fs::create_directory(s_CacheFolder);
    }

    std::string FileCacheManager::Set(const std::string& filename, const std::string& data)
    {
        std::ofstream file(GetRelativePath(filename), std::ios::trunc | std::ios::out | std::ios::binary);
        if (file)
            file << data;

        return data;
    }

    std::string FileCacheManager::Get(const std::string& filename)
    {
        std::ifstream file(GetRelativePath(filename), std::ios::in | std::ios::binary);
        std::string data;
        if (file)
            file >> data;

        return data;
    }
}