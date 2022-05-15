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
        inline void SetLoadingText(const std::string& text) { m_LoadingLabel.set_label(text); }
        inline void SetKeyCaptureWidget(Gtk::Widget& key_capture_widget) { m_SearchEntry.set_key_capture_widget(key_capture_widget); }
        void ToggleSearching(bool toggle = true);
        inline Gtk::Button& GetSearchButton() { return m_SearchButton; }

    protected:
        void handle_search();

    private:
        HeaderBar();
        void ClearCache();

    private:
        Gtk::SearchEntry m_SearchEntry;
        Gtk::Button m_SearchButton;
        Gtk::Label m_TitleLabel;
        Gtk::Spinner m_Spinner;
        Gtk::Label m_LoadingLabel;
        Gtk::PopoverMenu m_SettingsMenu;
        Gtk::MenuButton m_SettingsButton;

        Glib::RefPtr<Gio::SimpleActionGroup> m_SettingsActionGroup;
        Glib::ustring m_LastSearchedText;
    };
}

#define HEADER_BAR(func, ...) HeaderBar::_().func(__VA_ARGS__)

#endif //PRICECHECKER_HEADERBAR_H
