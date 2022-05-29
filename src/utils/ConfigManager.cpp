//
// Created by htrap19 on 5/5/22.
//

#include "ConfigManager.h"
#include <filesystem>
#include <fstream>

extern char _binary__default_config_json_start;
extern char _binary__default_config_json_end;

namespace PC
{
    namespace fs = std::filesystem;
    static fs::path s_ConfigFilePath = ".config.json";

    ConfigManager::ConfigManager()
    {
        std::ifstream config_file(s_ConfigFilePath);
        if (config_file.peek() != std::ifstream::traits_type::eof())
            config_file >> m_Root;

        if (!m_Root)
        {
            // create a new config.json
            std::stringstream default_config_content;
            default_config_content << std::string(&_binary__default_config_json_start, &_binary__default_config_json_end);
            default_config_content >> m_Root;
        }
    }

    ConfigManager::~ConfigManager()
    {
        std::ofstream config_file(s_ConfigFilePath);
        config_file << m_Root;
    }
}