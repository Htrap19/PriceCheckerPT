//
// Created by htrap19 on 5/4/22.
//

#ifndef PRICECHECKER_LANGUAGEMANAGER_H
#define PRICECHECKER_LANGUAGEMANAGER_H

#include <json/json.h>
#include <string>
#include <functional>
#include "utils/Utils.h"

namespace PC
{
    class LanguageManager // Single-Ton
    {
    public:
        SINGLE_TON(LanguageManager)

        std::string GetString(const std::string& key);
        [[maybe_unused]] std::string GetStringOfLang(const std::string& lang, const std::string& key);
        std::string GetFullNameOfLang(const std::string& lang);
        std::vector<std::string> GetLangPacks();

    protected:
        Json::Value GetLanguageData(const std::string& lang);

    private:
        LanguageManager();

    private:
        Json::Value m_Root;
        Json::Value m_Strings;

        static std::string s_CurrentLanguage;
    };
}

#define LANGUAGE(key) LanguageManager::_().GetString(#key)
#define LANG(func, ...) LanguageManager::_().func(__VA_ARGS__)

#endif //PRICECHECKER_LANGUAGEMANAGER_H
