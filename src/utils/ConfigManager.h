//
// Created by htrap19 on 5/5/22.
//

#ifndef PRICECHECKER_CONFIGMANAGER_H
#define PRICECHECKER_CONFIGMANAGER_H

#include "utils/Utils.h"
#include "utils/LanguageManager.h"
#include "components/InfoBar.h"
#include <json/json.h>

namespace PC
{
    class ConfigManager
    {
    public:
        ~ConfigManager();
        SINGLE_TON(ConfigManager)

        inline std::string GetLang() { return m_Root["lang"].asString(); }
        inline void SetLang(const std::string& lang) { m_Root["lang"] = lang; INFO_BAR(Info, LANGUAGE(after_language_changed_text)); }
        inline std::string GetCookiesPath(const std::string& name) { return m_Root["cookies"][name].asString(); }
        inline void SetCookiesPath(const std::string& name, const std::string& path) { m_Root["cookies"][name] = path; }

    private:
        ConfigManager();

    private:
        Json::Value m_Root;
    };
}

#define CONFIG(func, ...) ConfigManager::_().func(__VA_ARGS__)

#endif //PRICECHECKER_CONFIGMANAGER_H
