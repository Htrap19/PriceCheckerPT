//
// Created by Htrap19 on 3/22/2022.
//

#include "ProductComponent.h"

namespace ps
{
    static constexpr uint32_t ImagePixelSize = 128;

    ProductComponent::ProductComponent(const std::string& productName, const std::string& price, const std::string& img_path)
        : Gtk::Box(Gtk::Orientation::VERTICAL, 10),
        m_HBox(Gtk::Orientation::HORIZONTAL, 10),
        m_ProductName(productName),
        m_ProductPrice(price),
        m_ProductImage(img_path)
    {
        m_ProductImage.set_pixel_size(ImagePixelSize);
        set_valign(Gtk::Align::CENTER);
        set_halign(Gtk::Align::CENTER);

        m_HBox.prepend(m_ProductName);
        m_HBox.append(m_ProductPrice);
        m_ProductName.set_expand(true);
        m_ProductPrice.set_expand(true);

        prepend(m_ProductImage);
        append(m_HBox);
        m_HBox.set_expand(true);
    }
}