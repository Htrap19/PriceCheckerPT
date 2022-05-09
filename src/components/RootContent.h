//
// Created by htrap19 on 4/3/22.
//

#ifndef PRICECHECKER_ROOTCONTENT_H
#define PRICECHECKER_ROOTCONTENT_H

#include <gtkmm.h>
#include "SearchableContent.h"
#include "utils/Utils.h"

namespace PC
{
    class RootContent : public Gtk::Overlay // Single-Ton
    {
    public:
        SINGLE_TON(RootContent)

        void Search(const std::string& search_text);
        void Clear();

    private:
        RootContent();

    private:
        Gtk::Box m_MainHBox;
        Gtk::Stack m_Stack;
        Gtk::StackSidebar m_StackSidebar;

        std::vector<Glib::RefPtr<SearchableContent>> m_SearchableList;
    };
}

#endif //PRICECHECKER_ROOTCONTENT_H
