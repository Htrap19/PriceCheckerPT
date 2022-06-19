//
// Created by htrap19 on 5/29/22.
//

#include "AssetManager.h"
#include <unordered_map>
#include <stb_image.h>

#define IMPORT_ASSET_FROM_LINKER(name, type) extern char _binary_##name##_start; \
    extern char _binary_##name##_end;                          \
    static std::string get_##name##_content()                  \
    { return std::move(std::string(&_binary_##name##_start, &_binary_##name##_end)); } \
    static PC::AssetManager::AssetType get_##name##_type()                       \
    { return PC::AssetManager::AssetType::type; }                                \
    static std::string get_##name##_access_key()                                 \
    {                                                                            \
        std::string nameStr = #name;                                             \
        auto lastUnderScore = nameStr.find_last_of('_');                         \
        if (lastUnderScore != std::string::npos)                                 \
            return nameStr.substr(0, lastUnderScore);                            \
                                                                                 \
        return nameStr;                                                          \
    }

IMPORT_ASSET_FROM_LINKER(open_box_png, Image)
IMPORT_ASSET_FROM_LINKER(info_png, Image)
IMPORT_ASSET_FROM_LINKER(error_png, Image)
IMPORT_ASSET_FROM_LINKER(paragraph_png, Image)
IMPORT_ASSET_FROM_LINKER(question_png, Image)
IMPORT_ASSET_FROM_LINKER(warning_png, Image)
IMPORT_ASSET_FROM_LINKER(cookies_png, Image)

IMPORT_ASSET_FROM_LINKER(styles_css, Mics)

#define ADD_ASSET(name) auto accessKey##name = get_##name##_access_key();\
    if (get_##name##_type() == PC::AssetManager::AssetType::Image)       \
    {                                                                    \
        int width, height, nChannels;                                    \
        auto content = get_##name##_content();                           \
        auto data = stbi_load_from_memory((uint8_t*)content.c_str(), content.length(), &width, &height, &nChannels, 0); \
        auto pixbuf = Gdk::Pixbuf::create_from_data(data, Gdk::Colorspace::RGB, nChannels > 3, 8, width, height, width * nChannels); \
        s_Images[accessKey##name] = std::make_pair(data, pixbuf);        \
    }                                                                    \
    else if (get_##name##_type() == PC::AssetManager::AssetType::Mics)   \
        s_Mics[accessKey##name] = get_##name##_content;\

namespace PC
{
    static std::unordered_map<std::string, std::pair<uint8_t*, Glib::RefPtr<Gdk::Pixbuf>>> s_Images;
    static std::unordered_map<std::string, std::function<std::string()>> s_Mics;

    AssetManager::AssetManager()
    {
        ADD_ASSET(open_box_png)
        ADD_ASSET(info_png)
        ADD_ASSET(error_png)
        ADD_ASSET(paragraph_png)
        ADD_ASSET(question_png)
        ADD_ASSET(warning_png)
        ADD_ASSET(cookies_png)

        ADD_ASSET(styles_css)
    }

    AssetManager::~AssetManager()
    {
        for (auto& [ key, value ] : s_Images)
            stbi_image_free(value.first);
    }

    Glib::RefPtr<Gdk::Pixbuf> AssetManager::Image(const std::string& key)
    {
        if (s_Images.find(key) != s_Images.end())
            return s_Images[key].second;

        return nullptr;
    }

    std::string AssetManager::Mics(const std::string& key)
    {
        if (s_Mics.find(key) != s_Mics.end())
            return s_Mics[key]();

        return "";
    }
}