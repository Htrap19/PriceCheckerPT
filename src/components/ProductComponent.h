//
// Created by Htrap19 on 3/22/2022.
//

#ifndef PRICECHECKER_PRODUCTCOMPONENT_H
#define PRICECHECKER_PRODUCTCOMPONENT_H

#include <gtkmm.h>
#include "utils/Fetchable.h"

namespace ps
{
    class ProductComponent : public Gtk::Box, public Fetchable
    {
    public:
        ProductComponent(const std::string& productName, const std::string& price, const std::string& img_url);

        [[nodiscard]] inline std::string GetProductName() const { return m_ProductName.get_text(); }
        [[nodiscard]] inline std::string GetProductPrice() const { return m_ProductPrice.get_text(); }
        [[nodiscard]] inline std::string GetProductImagePath() const { return m_ProductImage.get_name(); }

    protected:
        void FetchErrCallback(const std::string& what) override;

    private:
        void FetchImage(std::string img_url);

    private:
        Gtk::Image m_ProductImage;
        Gtk::Box m_HBox;
        Gtk::Label m_ProductName;
        Gtk::Label m_ProductPrice;
    };
}

#endif //PRICECHECKER_PRODUCTCOMPONENT_H
