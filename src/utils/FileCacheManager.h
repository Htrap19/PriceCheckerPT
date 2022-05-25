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
    class FileCacheManager
    {
    public:
        static void Init();
        static std::string Set(const std::string& filename, const std::string& data);
        static std::string Get(const std::string& filename);
        static inline bool Check(const std::string& filename) { return fs::exists(GetRelativePath(filename)); }
        static inline std::string GetRelativePath(const std::string& filename) { return (s_CacheFolder / fs::path(filename)).generic_string(); }
        static inline void ClearCache() { fs::remove_all(s_CacheFolder); fs::create_directory(s_CacheFolder); }

    private:
        static fs::path s_CacheFolder;
    };
}

#endif //PRICECHECKER_FILECACHEMANAGER_H
