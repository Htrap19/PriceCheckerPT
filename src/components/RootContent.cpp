//
// Created by htrap19 on 4/3/22.
//

#include "RootContent.h"
#include "InfoBar.h"
#include "HeaderBar.h"
#include "ContinenteContent.h"
#include "AuchanContent.h"

namespace PC
{
    RootContent::RootContent()
        : m_MainHBox(Gtk::Orientation::HORIZONTAL, 10)
    {
        m_SearchableList.emplace_back(std::make_shared<ContinenteContent>());
        m_SearchableList.emplace_back(std::make_shared<AuchanContent>());

        for (auto& searchable : m_SearchableList)
            m_Stack.add(searchable->GetWidget(), searchable->GetName(), searchable->GetTitle());

        m_StackSidebar.set_stack(m_Stack);
        m_Stack.set_transition_type(Gtk::StackTransitionType::SLIDE_UP_DOWN);

        m_MainHBox.prepend(m_StackSidebar);
        m_MainHBox.append(m_Stack);
        m_Stack.set_expand();

        set_child(m_MainHBox);
        add_overlay(InfoBar::_());
    }

    void RootContent::Search(const std::string& search_text)
    {
        HeaderBar::_().ToggleSearching();
        for (auto& searchEntity : m_SearchableList)
            searchEntity->Search(search_text);
        InfoBar::_().Info("Search Finished!");
        HeaderBar::_().ToggleSearching(false);
    }
}