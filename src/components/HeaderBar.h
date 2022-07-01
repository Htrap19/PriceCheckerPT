//
// Created by htrap19 on 4/4/22.
//

#ifndef PRICECHECKER_HEADERBAR_H
#define PRICECHECKER_HEADERBAR_H

#include <gtkmm.h>
#include "utils/Utils.h"

namespace PC
{
    class HeaderBar : public Gtk::HeaderBar // Single-Ton
    {
    public:
        SINGLE_TON(HeaderBar)

        inline void SetTitle(const std::string& title) { m_TitleLabel.set_label(title); }
        inline void SetKeyCaptureWidget(Gtk::Widget& key_capture_widget) { m_SearchEntry.set_key_capture_widget(key_capture_widget); }
        void ToggleSearching(bool toggle = true);
        inline Gtk::Button& GetSearchButton() { return m_SearchButton; }
        inline void Notify() { m_NotificationDot.set_markup(PANGO_SMALL(std::to_string(++m_NotificationCount))); m_NotificationDot.show(); }

    protected:
        void handle_search();
        void handle_stop_search();

    private:
        HeaderBar();
        void ClearCache();

    private:
        Gtk::SearchEntry m_SearchEntry;
        Gtk::Button m_SearchButton;
        Gtk::Button m_StopSearchButton;
        Gtk::Label m_TitleLabel;
        Gtk::PopoverMenu m_SettingsMenu;
        Gtk::MenuButton m_SettingsButton;
        Gtk::ToggleButton m_NotificationButton;
        Gtk::Overlay m_NotificationOverlay;
        Gtk::Label m_NotificationDot;
        size_t m_NotificationCount = 0;

        Glib::RefPtr<Gio::SimpleActionGroup> m_SettingsActionGroup;
        Glib::ustring m_LastSearchedText;
    };
}

#define HEADER_BAR(func, ...) HeaderBar::_().func(__VA_ARGS__)

#endif //PRICECHECKER_HEADERBAR_H
