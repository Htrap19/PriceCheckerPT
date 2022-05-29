//
// Created by htrap19 on 5/29/22.
//

#ifndef PRICECHECKER_ASSETMANAGER_H
#define PRICECHECKER_ASSETMANAGER_H

#include "utils/Utils.h"
#include <gtkmm.h>

namespace PC
{
    class AssetManager
    {
    public:
        enum class AssetType
        {
            Unknown = -1,
            Image,
            Mics
        };

    public:
        ~AssetManager();
        SINGLE_TON(AssetManager)

        Glib::RefPtr<Gdk::Pixbuf> Image(const std::string& key);
        std::string Mics(const std::string& key);

    private:
        AssetManager();
    };

#define ASSET(func, ...) AssetManager::_().func(__VA_ARGS__)
}

#endif //PRICECHECKER_ASSETMANAGER_H
