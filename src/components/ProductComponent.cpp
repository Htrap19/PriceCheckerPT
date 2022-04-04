//
// Created by Htrap19 on 3/22/2022.
//

#include "ProductComponent.h"
#include "InfoBar.h"
#include "utils/FileCacheManager.h"
#include "utils/CssProvider.h"
#include <thread>

namespace PC
{
    static constexpr uint8_t s_ImagePixelSize = 64;
    std::mutex ProductComponent::s_FileCacheMutex;

    ProductComponent::ProductComponent(const std::string& productName, const std::string& price, const std::string& img_url)
        : m_MainHBox(Gtk::Orientation::HORIZONTAL, 10),
        m_VBox(Gtk::Orientation::VERTICAL),
        m_ProductPrice(price, Gtk::Align::START)
    {
        m_ProductImage.set_pixel_size(s_ImagePixelSize);
        CssProvider::LoadProvider((Gtk::Widget&)*this);

        m_ProductName.set_markup("<b>" + productName + "</b>");

        m_VBox.set_valign(Gtk::Align::CENTER);
        m_VBox.set_halign(Gtk::Align::START);
        m_VBox.prepend(m_ProductName);
        m_VBox.append(m_ProductPrice);

        m_MainHBox.prepend(m_ProductImage);
        m_MainHBox.append(m_VBox);
        m_VBox.set_expand();

        set_child(m_MainHBox);
        add_css_class("list_row");

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

        std::lock_guard lock(s_FileCacheMutex);
        auto& fcm = FileCacheManager::_();
        if (!fcm.Check(img_name))
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