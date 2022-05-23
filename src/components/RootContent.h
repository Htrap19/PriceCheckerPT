//
// Created by htrap19 on 4/3/22.
//

#ifndef PRICECHECKER_ROOTCONTENT_H
#define PRICECHECKER_ROOTCONTENT_H

#include <gtkmm.h>
#include "components/SearchableContent.h"
#include "utils/Utils.h"

namespace PC
{
    class RootContent : public Gtk::Overlay // Single-Ton
    {
    public:
        SINGLE_TON(RootContent)

        void Search(const std::string& search_text);
        void ClearResult();
        inline void NavigateToCompare() { m_Stack.set_visible_child("compare", Gtk::StackTransitionType::SLIDE_LEFT_RIGHT); }
        inline const std::list<Glib::RefPtr<SearchableContent>>& GetSearchableList() const { return m_SearchableList; }

    private:
        RootContent();

    private:
        Gtk::Box m_MainHBox;
        Gtk::Stack m_Stack;
        Gtk::StackSidebar m_StackSidebar;

        std::list<Glib::RefPtr<SearchableContent>> m_SearchableList;
    };
}

#endif //PRICECHECKER_ROOTCONTENT_H
