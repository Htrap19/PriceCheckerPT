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
        ProductComponent(const std::string& productName,
                         const std::string& productBrand,
                         const std::string& productPackaging,
                         const std::string& originalPrice,
                         const std::string& actualPrice,
                         const std::string& secondaryPriceDesc,
                         const std::string& img_url,
                         bool img_resize = false);
        void AddToSizeGroup();

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
