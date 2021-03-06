//
// Created by Htrap19 on 3/22/2022.
//

#include "ProductComponent.h"
#include "InfoBar.h"
#include "utils/FileCacheManager.h"
#include "utils/LanguageManager.h"
#include "utils/Utils.h"

namespace PC
{
    static Glib::RefPtr<Gtk::SizeGroup> s_PriceSizeGroup = Gtk::SizeGroup::create(Gtk::SizeGroup::Mode::BOTH);

    ProductComponent::ProductComponent(const Glib::ustring& productName,
                                       const Glib::ustring& productBrand,
                                       const Glib::ustring& productPackaging,
                                       const Glib::ustring& originalPrice,
                                       const Glib::ustring& actualPrice,
                                       const Glib::ustring& secondaryPriceDesc,
                                       const Glib::ustring& img_url,
                                       bool img_resize)
        : m_MainHBox(Gtk::Orientation::HORIZONTAL, 10),
        m_ProductName(productName, Gtk::Align::START),
        m_VBox(Gtk::Orientation::VERTICAL),
        m_ProductDescHBox(Gtk::Orientation::HORIZONTAL, 10),
        m_ProductBrand(CHECK_EMPTY_STRING(productBrand), Gtk::Align::START, Gtk::Align::CENTER),
        m_ProductPackaging(CHECK_EMPTY_STRING(productPackaging)),
        m_ProductPriceVBox(Gtk::Orientation::VERTICAL, 10),
        m_ProductActualPrice(actualPrice, Gtk::Align::CENTER, Gtk::Align::CENTER),
        m_ProductSecondaryPriceDesc(CHECK_EMPTY_STRING(secondaryPriceDesc), Gtk::Align::CENTER, Gtk::Align::CENTER),
        m_ProductPriceSep(Gtk::Orientation::VERTICAL)
    {
        m_ProductImage.set_pixel_size(ImagePixelSize);

        m_ProductName.set_markup(Glib::locale_to_utf8(PANGO_BOLD(productName)));

        m_ProductPackaging.set_markup(Glib::locale_to_utf8(PANGO_SMALL(productPackaging)));

        m_ProductDescHBox.prepend(m_ProductBrand);
        m_ProductDescHBox.append(m_ProductPackaging);
        if (productBrand.empty() && productPackaging.empty())
            m_ProductDescHBox.unmap();

        m_VBox.set_valign(Gtk::Align::CENTER);
        m_VBox.set_halign(Gtk::Align::START);
        m_VBox.prepend(m_ProductName);
        m_VBox.append(m_ProductDescHBox);

        m_MainHBox.prepend(m_ProductImage);
        m_MainHBox.append(m_VBox);
        m_VBox.set_expand();

        m_ProductOriginalPrice.set_markup(Glib::locale_to_utf8(PANGO_STRIKETHROUGH(PANGO_SMALL(CHECK_EMPTY_STRING(originalPrice)))));

        m_ProductPriceVBox.set_valign(Gtk::Align::CENTER);
        m_ProductPriceVBox.set_halign(Gtk::Align::CENTER);
        m_ProductPriceVBox.prepend(m_ProductOriginalPrice);
        m_ProductPriceVBox.append(m_ProductActualPrice);

        m_ProductPriceSep.set_margin_start(10);
        m_ProductPriceSep.set_margin_end(10);
        m_MainHBox.append(m_ProductSecondaryPriceDesc);
        m_MainHBox.append(m_ProductPriceSep);
        m_MainHBox.append(m_ProductPriceVBox);

//        m_MainHBox.set_margin(10);
        set_child(m_MainHBox);
        add_css_class("list_row");

        FetchImage(img_url, img_resize);
    }

    void ProductComponent::AddToSizeGroup()
    {
        s_PriceSizeGroup->add_widget(m_ProductPriceVBox);
    }

    static std::string ExtractNameFromUrl(std::string& url, bool img_resize)
    {
        auto lastQuesMark = url.rfind('?');
        if (lastQuesMark != std::string::npos) url.erase(lastQuesMark);

        auto lastSlash = url.find_last_of('/');
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;

        auto name = url.substr(lastSlash);
        if (img_resize)
        {
            std::string sizeStr = "?sw=" + std::to_string(ProductComponent::ImagePixelSize) + "&sh=" + std::to_string(ProductComponent::ImagePixelSize);
            url += sizeStr;
        }
        return name;
    }

    void ProductComponent::FetchImage(std::string img_url, bool img_resize)
    {
        if (!img_url.starts_with("http"))
        {
            FetchErrCallback(LANGUAGE(url_validation_failed));
            return;
        }

        auto img_name = ExtractNameFromUrl(img_url, img_resize);

        if (!FileCacheManager::Check(img_name))
        {
            std::string data = std::move(FetchBase(img_url, true).str());
            FileCacheManager::Set(img_name, data);
        }

        m_ProductImage.set(FileCacheManager::GetRelativePath(img_name));
    }

    void ProductComponent::FetchErrCallback(const std::string& what)
    {
        INFO_BAR(Error, what);
    }
}