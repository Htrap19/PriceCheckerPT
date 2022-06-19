//
// Created by htrap19 on 5/4/22.
//

#include "LanguageManager.h"
#include "utils/ConfigManager.h"
#include <iostream>
#include <functional>

#define IMPORT_LANGUAGE(lang) extern char _binary_##lang##_json_start;       \
    extern char _binary_##lang##_json_end;                                   \
    static std::string get_content_##lang()                                  \
    { return std::move(std::string(&_binary_##lang##_json_start, &_binary_##lang##_json_end)); }

IMPORT_LANGUAGE(en)
IMPORT_LANGUAGE(pt)

#define ADD_LANGUAGE(lang) s_LangPacks[#lang] = get_content_##lang

namespace PC
{
    static std::unordered_map<std::string, std::function<std::string()>> s_LangPacks;
    std::string LanguageManager::s_CurrentLanguage;

    LanguageManager::LanguageManager()
    {
        // Add language packs to the application
        ADD_LANGUAGE(pt);
        ADD_LANGUAGE(en); // default or fallback language (last one will be the fallback language)

        // get lang from config file
        s_CurrentLanguage = CONFIG(GetLang);

        m_Root = GetLanguageData(s_CurrentLanguage);
        if (!m_Root || m_Root.type() != Json::ValueType::objectValue)
        {
            std::cout << "Unable to recognize json lang pack format!" << std::endl;
            return;
        }

        m_Strings = m_Root["strings"];
    }

    std::string LanguageManager::GetString(const std::string& key)
    {
        auto value = m_Strings[key];
        if (value) return value.asString();

        return "";
    }

    [[maybe_unused]] std::string LanguageManager::GetStringOfLang(const std::string& lang, const std::string& key)
    {
        auto langData = GetLanguageData(lang);
        auto value = langData["strings"][key];
        if (value) return value.asString();

        return "";
    }

    std::string LanguageManager::GetFullNameOfLang(const std::string& lang)
    {
        auto landData = GetLanguageData(lang);
        auto fullname = landData["fullname"];
        if (fullname) return fullname.asString();

        return "";
    }

    std::vector<std::string> LanguageManager::GetLangPacks()
    {
        std::vector<std::string> langPacks;
        for (auto& [ lang, data ] : s_LangPacks)
            langPacks.emplace_back(lang);

        return std::move(langPacks);
    }

    Json::Value LanguageManager::GetLanguageData(const std::string& lang)
    {
        Json::Value root;
        auto langData = (s_LangPacks.contains(lang)) ? s_LangPacks[lang] : s_LangPacks.begin()->second;
        std::stringstream content;
        content << langData();
        content >> root;
        return root;
    }
}