//
// Created by htrap19 on 4/3/22.
//

#ifndef PRICECHECKER_ROOTCONTENT_H
#define PRICECHECKER_ROOTCONTENT_H

#include <gtkmm.h>
#include "utils/Searchable.h"

namespace PC
{
    class RootContent : public Gtk::Overlay // Single-Ton
    {
    public:
        RootContent(RootContent&) = delete;
        RootContent(RootContent&&) = delete;
        RootContent& operator=(RootContent&) = delete;
        RootContent& operator=(RootContent&&) = delete;

        inline static RootContent& _() { static RootContent instance; return instance; }

        void Search(const std::string& search_text);

    private:
        RootContent();

    private:
        Gtk::Box m_MainHBox;
        Gtk::Stack m_Stack;
        Gtk::StackSidebar m_StackSidebar;

        std::vector<Glib::RefPtr<Searchable>> m_SearchableList;
    };
}

#endif //PRICECHECKER_ROOTCONTENT_H
