//
// Created by htrap19 on 3/28/22.
//

#ifndef PRICECHECKER_FILECACHEMANAGER_H
#define PRICECHECKER_FILECACHEMANAGER_H

#include <string>
#include <filesystem>
#include "utils/Utils.h"

namespace PC
{
    namespace fs = std::filesystem;
    class FileCacheManager // Single-Ton
    {
    public:
        SINGLE_TON(FileCacheManager)

        std::string Set(const std::string& filename, const std::string& data);
        std::string Get(const std::string& filename);
        bool Check(const std::string& filename);
        inline std::string GetRelativePath(const std::string& filename) { return (s_CacheFolder / fs::path(filename)).generic_string(); }
        inline void ClearCache() const { fs::remove_all(s_CacheFolder); }

    private:
        FileCacheManager();

    private:
        static fs::path s_CacheFolder;
    };
}

#endif //PRICECHECKER_FILECACHEMANAGER_H
