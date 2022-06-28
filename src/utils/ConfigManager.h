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
        inline void SetWatchListProduct(const std::string& name, const std::string& product_name, const std::string& details_base64) { m_Root["watch_list"][name][product_name] = details_base64; }
        [[nodiscard]] inline Json::Value& GetWatchList() { return m_Root["watch_list"]; }
        [[nodiscard]] inline Json::Value& GetWatchListStore(const std::string& name) { return GetWatchList()[name]; }
        [[nodiscard]] inline Json::Value& GetWatchListProduct(const std::string& store_name, const std::string& product_name) { return GetWatchListStore(store_name)[product_name]; }
        void RemoveWatchListStore(const std::string& name);
        void RemoveWatchListProduct(const std::string& store_name, const std::string& product_name);

    private:
        ConfigManager();

    private:
        Json::Value m_Root;
    };
}

#define CONFIG(func, ...) ConfigManager::_().func(__VA_ARGS__)

#endif //PRICECHECKER_CONFIGMANAGER_H
