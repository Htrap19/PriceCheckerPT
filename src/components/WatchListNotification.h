//
// Created by htrap19 on 6/26/22.
//

#ifndef PRICECHECKER_WATCHLISTNOTIFICATION_H
#define PRICECHECKER_WATCHLISTNOTIFICATION_H

#include <gtkmm.h>
#include <unordered_set>
#include "components/ProductComponent.h"
#include "components/EmptyList.h"
#include "utils/Utils.h"

namespace PC
{
    class Component : public Gtk::ListBoxRow
    {
    public:
        Component(const Glib::RefPtr<Gdk::Paintable>& image_paintable, const Glib::ustring& name,
                  const Glib::ustring& old_actual_price, const Glib::ustring& old_original_price,
                  const Glib::ustring& old_price_desc);

        void ChangedTo(const Glib::ustring& new_actual_price, const Glib::ustring& new_original_price,
                       const Glib::ustring& new_price_desc);

        inline bool operator==(const Component& other)
        { return m_Name.get_text() == other.m_Name.get_text(); }
        inline bool operator==(const Component& other) const
        { return m_Name.get_text() == other.m_Name.get_text(); }

    private:
        // Used for std::hash<Component>
        inline size_t operator()() const noexcept
        { return std::hash<std::string>()(m_Name.get_text()); }

    private:
        // Data
        Gtk::Image m_Image;
        Gtk::Label m_Name;
        Gtk::Label m_OldActualPrice, m_OldOriginalPrice, m_OldPriceDesc;
        Gtk::Label m_NewActualPrice, m_NewOriginalPrice, m_NewPriceDesc;

        // Layout
        Gtk::Box m_MainHBox, m_OldPriceVBox, m_NewPriceVBox;
        Gtk::Image m_ToArrowImage;

        friend struct std::hash<Component>;
    };
}

namespace std
{
    template <>
    struct hash<PC::Component>
    {
        size_t operator()(const PC::Component& comp) const noexcept
        { return comp(); }
    };
}

namespace PC
{
    class WatchListNotification : public Gtk::ScrolledWindow
    {
    public:
        SINGLE_TON(WatchListNotification)

        void Notify(ProductComponent& comp, const Glib::ustring& old_actual_price,
                    const Glib::ustring& old_original_price, const Glib::ustring& old_price_desc);

    private:
        WatchListNotification();

    private:
        Gtk::ListBox m_ListBox;
        EmptyList m_EmptyList;
        std::unordered_set<Component> m_Notifications;
    };
}

#endif //PRICECHECKER_WATCHLISTNOTIFICATION_H
