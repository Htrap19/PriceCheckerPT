//
// Created by htrap19 on 6/26/22.
//

#include "WatchListNotification.h"
#include "utils/CssProvider.h"

namespace PC
{
    static Glib::RefPtr<Gtk::SizeGroup> s_ProductSizeGroup = Gtk::SizeGroup::create(Gtk::SizeGroup::Mode::BOTH);

    WatchListNotification::Component::Component(const Glib::RefPtr<Gdk::Paintable>& image_paintable, const Glib::ustring& name,
                                                const Glib::ustring& old_actual_price,
                                                const Glib::ustring& old_original_price,
                                                const Glib::ustring& old_price_desc)
        : m_Image(image_paintable), m_OldActualPrice(old_actual_price), m_OldPriceDesc(old_price_desc),
        m_MainHBox(Gtk::Orientation::HORIZONTAL), m_OldPriceVBox(Gtk::Orientation::VERTICAL, 10),
        m_NewPriceVBox(Gtk::Orientation::VERTICAL, 10)
    {
        m_Name.set_markup(Glib::locale_to_utf8(PANGO_BOLD(name))),
        m_Name.set_halign(Gtk::Align::START);
        m_OldOriginalPrice.set_markup(Glib::locale_to_utf8(PANGO_STRIKETHROUGH(PANGO_SMALL(old_original_price)))),

        m_Image.set_pixel_size((int32_t)ProductComponent::ImagePixelSize);
        m_Image.set_margin_end(5);
        m_ToArrowImage.set_from_icon_name("object-flip-horizontal");
        m_ToArrowImage.set_valign(Gtk::Align::CENTER);
        m_ToArrowImage.set_margin_start(30);
        m_ToArrowImage.set_margin_end(30);

        m_OldPriceVBox.prepend(m_OldOriginalPrice);
        m_OldPriceVBox.append(m_OldActualPrice);
        m_OldPriceVBox.set_valign(Gtk::Align::CENTER);

        m_NewPriceVBox.prepend(m_NewOriginalPrice);
        m_NewPriceVBox.append(m_NewActualPrice);
        m_NewPriceVBox.set_valign(Gtk::Align::CENTER);

        auto firstSep = Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::VERTICAL);
        firstSep->set_margin_start(10);
        firstSep->set_margin_end(10);

        auto secondSep = Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::VERTICAL);
        secondSep->set_margin_start(10);
        secondSep->set_margin_end(10);

        auto priceChangesHBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);

        priceChangesHBox->append(m_OldPriceDesc);
        priceChangesHBox->append(*firstSep);
        priceChangesHBox->append(m_OldPriceVBox);
        priceChangesHBox->append(m_ToArrowImage);
        priceChangesHBox->append(m_NewPriceDesc);
        priceChangesHBox->append(*secondSep);
        priceChangesHBox->append(m_NewPriceVBox);
        s_ProductSizeGroup->add_widget(*priceChangesHBox);

        m_MainHBox.prepend(m_Image);
        m_MainHBox.append(m_Name);
        m_Name.set_expand();
        m_MainHBox.append(*priceChangesHBox);

        set_child(m_MainHBox);
        CssProvider::LoadProvider((Gtk::Widget&)*this);
        add_css_class("list_row");
    }

    void WatchListNotification::Component::ChangedTo(const Glib::ustring& new_actual_price,
                                                     const Glib::ustring& new_original_price,
                                                     const Glib::ustring& new_price_desc)
    {
        m_NewOriginalPrice.set_markup(Glib::locale_to_utf8(PANGO_STRIKETHROUGH(PANGO_SMALL(new_original_price))));
        m_NewActualPrice.set_text(Glib::locale_to_utf8(new_actual_price));
        m_NewPriceDesc.set_text(Glib::locale_to_utf8(new_price_desc));
    }

    WatchListNotification::WatchListNotification()
        : m_EmptyList("No notifications")
    {
        CssProvider::LoadProvider(m_ListBox);
        m_ListBox.add_css_class("padding-10");
        m_ListBox.set_selection_mode(Gtk::SelectionMode::MULTIPLE);
        m_ListBox.set_show_separators();
        m_ListBox.set_placeholder(m_EmptyList);

        set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        set_child(m_ListBox);
    }

    void WatchListNotification::Notify(ProductComponent& comp, const Glib::ustring& old_actual_price,
                                       const Glib::ustring& old_original_price, const Glib::ustring& old_price_desc)
    {
        Component component(comp.GetProductImage(), comp.GetProductName(), old_actual_price,
                            old_original_price, old_price_desc);
        component.ChangedTo(comp.GetProductActualPrice(), comp.GetProductOriginalPrice(), comp.GetProductSecondaryPriceDesc());

        m_ListBox.append(component);
    }
}