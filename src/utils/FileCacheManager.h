//
// Created by htrap19 on 3/28/22.
//

#ifndef PRICECHECKER_FILECACHEMANAGER_H
#define PRICECHECKER_FILECACHEMANAGER_H

#include <string>

namespace ps
{
    class FileCacheManager // SingleTon
    {
    public:
        FileCacheManager(FileCacheManager&) = delete;
        FileCacheManager(FileCacheManager&&) = delete;
        FileCacheManager& operator=(FileCacheManager&) = delete;
        FileCacheManager& operator=(FileCacheManager&&) = delete;

        inline static FileCacheManager& _() { static FileCacheManager instance; return instance; }

        std::string Set(const std::string& filename, const std::string& data);
        std::string Get(const std::string& filename);
        bool Check(const std::string& filename);
        inline std::string GetRelativePath(const std::string& filename) { return s_TempFolderLocation + filename; }

    private:
        FileCacheManager();

    private:
        static std::string s_TempFolderLocation;
    };
}

#endif //PRICECHECKER_FILECACHEMANAGER_H
