//
// Created by Htrap19 on 3/22/2022.
//

#ifndef PRICECHECKER_ROOTVBOX_H
#define PRICECHECKER_ROOTVBOX_H

#include <gtkmm.h>
#include "ContentVBox.h"

namespace ps
{
    class RootVBox : public Gtk::Overlay // SingleTon
    {
    public:
        RootVBox(RootVBox&) = delete;
        RootVBox(RootVBox&&) = delete;
        RootVBox& operator=(RootVBox&) = delete;
        RootVBox& operator=(RootVBox&&) = delete;

        inline static RootVBox& _() { static RootVBox instance; return instance; }

        inline void SearchButtonSensitive(bool sensitive) { m_SearchButton.set_sensitive(sensitive); }
        inline bool SearchButtonSensitive() const { return m_SearchButton.get_sensitive(); }
        inline void SearchSpinnerStart() { m_SearchingSpinner.start(); }
        inline void SearchSpinnerStop() { m_SearchingSpinner.stop(); }

    private:
        RootVBox();
        void search_stop();
        void handle_search();

    private:
        Gtk::Box m_MainVBox;
        Gtk::Box m_SearchHBox;
        Gtk::Button m_SearchButton;
        Gtk::SearchEntry m_SearchEntry;
        Gtk::Spinner m_SearchingSpinner;
        Gtk::SearchBar m_SearchBar;

        ContentVBox m_Content;
    };
}

#endif //PRICECHECKER_ROOTVBOX_H
