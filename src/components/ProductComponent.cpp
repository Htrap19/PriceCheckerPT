//
// Created by Htrap19 on 3/22/2022.
//

#include "ProductComponent.h"
#include "InfoBar.h"
#include "utils/FileCacheManager.h"
#include <fstream>
#include <thread>
#include <mutex>

namespace ps
{
    static constexpr uint32_t s_ImagePixelSize = 128;
//    static const std::string s_TempFolderLocation = ".cache/";

    ProductComponent::ProductComponent(const std::string& productName, const std::string& price, const std::string& img_url)
        : Gtk::Box(Gtk::Orientation::VERTICAL, 10),
        m_HBox(Gtk::Orientation::HORIZONTAL, 10),
        m_ProductName(productName),
        m_ProductPrice(price)
    {
        m_ProductImage.set_pixel_size(s_ImagePixelSize);
        set_valign(Gtk::Align::CENTER);
        set_halign(Gtk::Align::CENTER);

        m_HBox.prepend(m_ProductName);
        m_HBox.append(m_ProductPrice);
        m_ProductName.set_expand(true);
        m_ProductPrice.set_expand(true);

        prepend(m_ProductImage);
        append(m_HBox);
        m_HBox.set_expand(true);

        FetchImage(img_url);
    }

    static std::string ExtractNameFromUrl(std::string& url)
    {
        auto lastQuesMark = url.rfind('?');
        if (lastQuesMark != std::string::npos) url.erase(lastQuesMark);

        auto lastSlash = url.find_last_of('/');
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;

        return url.substr(lastSlash);
    }

    void ProductComponent::FetchImage(std::string img_url)
    {
        if (img_url.find("http") == std::string::npos)
        {
            FetchErrCallback("Url validation failed!");
            return;
        }

        auto img_name = ExtractNameFromUrl(img_url);

        std::string data;
        auto& fcm = FileCacheManager::_();
        if (fcm.Check(img_name))
            data = fcm.Get(img_name);
        else
        {
            data = std::move(FetchBase(img_url).str());
            fcm.Set(img_name, data);
        }

        m_ProductImage.set(Gdk::Pixbuf::create_from_file(fcm.GetRelativePath(img_name)));
    }

    void ProductComponent::FetchErrCallback(const std::string& what)
    {
        InfoBar::_().Error(what);
    }
}