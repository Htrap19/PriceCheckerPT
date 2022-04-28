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
        inline void ToggleSearching(bool toggle = true) { m_SearchButton.set_sensitive(!toggle); m_SearchEntry.set_sensitive(!toggle); (toggle ? m_Spinner.start() : m_Spinner.stop()); }
        inline Gtk::Button& GetSearchButton() { return m_SearchButton; }

    protected:
        void handle_search();

    private:
        explicit HeaderBar(Gtk::Widget& key_capture_widget);

    private:
        Gtk::SearchEntry m_SearchEntry;
        Gtk::Button m_SearchButton;
        Gtk::Label m_TitleLabel;
        Gtk::Spinner m_Spinner;
    };
}

#endif //PRICECHECKER_HEADERBAR_H
