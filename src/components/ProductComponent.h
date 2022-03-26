//
// Created by Htrap19 on 3/22/2022.
//

#ifndef PRICECHECKER_PRODUCTCOMPONENT_H
#define PRICECHECKER_PRODUCTCOMPONENT_H

#include <gtkmm.h>

namespace ps
{
    class ProductComponent : public Gtk::Box
    {
    public:
        ProductComponent(const std::string& productName, const std::string& price, const std::string& img_path);

        [[nodiscard]] inline std::string GetProductName() const { return m_ProductName.get_text(); }
        [[nodiscard]] inline std::string GetProductPrice() const { return m_ProductPrice.get_text(); }
        [[nodiscard]] inline std::string GetProductImagePath() const { return m_ProductImage.get_icon_name(); }

    private:
        Gtk::Image m_ProductImage;
        Gtk::Box m_HBox;
        Gtk::Label m_ProductName;
        Gtk::Label m_ProductPrice;
    };
}

#endif //PRICECHECKER_PRODUCTCOMPONENT_H
