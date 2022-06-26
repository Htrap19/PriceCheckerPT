//
// Created by Htrap19 on 3/22/2022.
//

#ifndef PRICECHECKER_PRODUCTCOMPONENT_H
#define PRICECHECKER_PRODUCTCOMPONENT_H

#include <gtkmm.h>
#include "utils/Fetchable.h"

namespace PC
{
    class ProductComponent : public Gtk::ListBoxRow, public Fetchable
    {
    public:
        static constexpr uint32_t ImagePixelSize = 64;

    public:
        ProductComponent(const Glib::ustring& productName,
                         const Glib::ustring& productBrand,
                         const Glib::ustring& productPackaging,
                         const Glib::ustring& originalPrice,
                         const Glib::ustring& actualPrice,
                         const Glib::ustring& secondaryPriceDesc,
                         const Glib::ustring& img_url,
                         bool img_resize = false);
        void AddToSizeGroup();

        inline Glib::ustring GetProductName() const { return m_ProductName.get_text(); }
        inline Glib::ustring GetProductBrand() const { return m_ProductBrand.get_text(); }
        inline Glib::ustring GetProductPackaging() const { return m_ProductPackaging.get_text(); }
        inline Glib::ustring GetProductActualPrice() const { return m_ProductActualPrice.get_text(); }
        inline Glib::ustring GetProductOriginalPrice() const { return m_ProductOriginalPrice.get_text(); }
        inline Glib::ustring GetProductSecondaryPriceDesc() const { return m_ProductSecondaryPriceDesc.get_text(); }
        inline Glib::RefPtr<Gdk::Paintable> GetProductImage() { return m_ProductImage.get_paintable(); }

    protected:
        void FetchErrCallback(const std::string& what) override;

    private:
        void FetchImage(std::string img_url, bool img_resize);

    private:
        Gtk::Box m_MainHBox;
        Gtk::Image m_ProductImage;
        Gtk::Box m_VBox;
        Gtk::Label m_ProductName;
        Gtk::Box m_ProductDescHBox;
        Gtk::Label m_ProductBrand;
        Gtk::Label m_ProductPackaging;
        Gtk::Box m_ProductPriceVBox;
        Gtk::Label m_ProductActualPrice;
        Gtk::Label m_ProductOriginalPrice;
        Gtk::Label m_ProductSecondaryPriceDesc;
        Gtk::Separator m_ProductPriceSep;
    };
}

#endif //PRICECHECKER_PRODUCTCOMPONENT_H
