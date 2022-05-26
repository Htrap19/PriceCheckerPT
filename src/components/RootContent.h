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
        using SearchableContentType = Glib::RefPtr<SearchableContent>;

    public:
        SINGLE_TON(RootContent)

        void Search(const std::string& search_text);
        void ToggleSearching(bool toggle = true);
        void ClearResult();
        void StopSearch();
        inline bool IsCompleted() const { return std::all_of(m_SearchableList.begin(), m_SearchableList.end(), [](const SearchableContentType& searchEntity) { return searchEntity->IsCompleted(); }); }
        inline void NavigateToCompare() { m_Stack.set_visible_child("compare", Gtk::StackTransitionType::SLIDE_LEFT_RIGHT); }
        inline const std::list<SearchableContentType>& GetSearchableList() const { return m_SearchableList; }

    private:
        RootContent();
        static Gtk::ListBoxRow* MakeSidebarItem(const SearchableContentType& searchable_content);

    private:
        Gtk::Box m_MainHBox;
        Gtk::Stack m_Stack;
        Gtk::ListBox m_SidebarListBox;

        std::list<SearchableContentType> m_SearchableList;
    };
}

#endif //PRICECHECKER_ROOTCONTENT_H
