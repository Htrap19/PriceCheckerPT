//
// Created by htrap19 on 4/3/22.
//

#include <thread>
#include "RootContent.h"
#include "InfoBar.h"
#include "HeaderBar.h"
#include "components/stores/ContinenteContent.h"
#include "components/stores/AuchanContent.h"
#include "components/stores/MiniprecoContent.h"
#include "components/stores/ElcorteinglesContent.h"
#include "components/stores/SparContent.h"
#include "utils/TaskQueue.h"
#include "utils/LanguageManager.h"
#include "utils/UIQueue.h"

namespace PC
{
    RootContent::RootContent()
        : m_MainHBox(Gtk::Orientation::HORIZONTAL, 10)
    {
        m_SearchableList.emplace_back(std::make_shared<ContinenteContent>());
        m_SearchableList.emplace_back(std::make_shared<AuchanContent>());
        m_SearchableList.emplace_back(std::make_shared<MiniprecoContent>());
        m_SearchableList.emplace_back(std::make_shared<ElcorteinglesContent>());
        m_SearchableList.emplace_back(std::make_shared<SparContent>());

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
        UIQueue::_().Push([&]() { ClearResult(); HEADER_BAR(ToggleSearching); });

        for (auto& searchEntity : m_SearchableList)
            searchEntity->Search(search_text);
        TaskQueue::_().SetIdleCallback([&]()
        {
            UIQueue::_().Push([&]()
            {
                INFO_BAR(Info, LANGUAGE(search_finished));
                HEADER_BAR(ToggleSearching, false);
            });
        });
    }

    void RootContent::ClearResult()
    {
        for (auto& searchEntity : m_SearchableList)
            searchEntity->ClearProductList();
    }
}