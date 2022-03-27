//
// Created by Htrap19 on 3/22/2022.
//

#ifndef PRICECHECKER_ROOTVBOX_H
#define PRICECHECKER_ROOTVBOX_H

#include <gtkmm.h>
#include "ContentVBox.h"

namespace ps
{
    class RootVBox : public Gtk::Overlay
    {
    public:
        RootVBox();

    private:
        void search_stop();
        void handle_search();

    private:
        Gtk::Box m_MainVBox;
        Gtk::Box m_SearchHBox;
        Gtk::Button m_SearchButton;
        Gtk::SearchEntry m_SearchEntry;
        Gtk::SearchBar m_SearchBar;

        ContentVBox m_Content;
    };
}

#endif //PRICECHECKER_ROOTVBOX_H
