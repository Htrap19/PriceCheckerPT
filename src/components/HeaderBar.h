//
// Created by htrap19 on 4/4/22.
//

#ifndef PRICECHECKER_HEADERBAR_H
#define PRICECHECKER_HEADERBAR_H

#include <gtkmm.h>

namespace PC
{
    class HeaderBar : public Gtk::HeaderBar // Single-Ton
    {
    public:
        HeaderBar(HeaderBar&) = delete;
        HeaderBar(HeaderBar&&) = delete;
        HeaderBar& operator=(HeaderBar&) = delete;
        HeaderBar& operator=(HeaderBar&&) = delete;

        inline static HeaderBar& _(Gtk::Widget& key_capture_widget) { static HeaderBar instance(key_capture_widget); return instance; }

        inline void SetTitle(const std::string& title) { m_TitleLabel.set_label(title); }
        void ToggleSearching(bool toggle = true);
        inline Gtk::Button& GetSearchButton() { return m_SearchButton; }

    protected:
        void handle_search();

    private:
        explicit HeaderBar(Gtk::Widget& key_capture_widget);
        void ClearCache();

    private:
        Gtk::SearchEntry m_SearchEntry;
        Gtk::Button m_SearchButton;
        Gtk::Label m_TitleLabel;
        Gtk::Spinner m_Spinner;
        Gtk::PopoverMenu m_SettingsMenu;
        Gtk::MenuButton m_SettingsButton;

        Glib::RefPtr<Gio::SimpleActionGroup> m_SettingsActionGroup;
    };
}

#endif //PRICECHECKER_HEADERBAR_H
