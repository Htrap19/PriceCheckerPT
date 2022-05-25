//
// Created by htrap19 on 4/3/22.
//

#include "RootContent.h"
#include "InfoBar.h"
#include "HeaderBar.h"
#include "components/stores/ContinenteContent.h"
#include "components/stores/AuchanContent.h"
#include "components/stores/MiniprecoContent.h"
#include "components/stores/ElcorteinglesContent.h"
#include "components/stores/SparContent.h"
#include "components/CompareComponent.h"
#include "utils/TaskQueue.h"
//#include "utils/LanguageManager.h"
#include "utils/UIQueue.h"
#include "utils/CssProvider.h"

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
        {
            m_Stack.add(searchable->GetWidget(), searchable->GetName());
            auto row = MakeSidebarItem(searchable);
            m_SidebarListBox.append(*row);
        }

        m_Stack.add(CompareComponent::_(), "compare");
        m_Stack.set_transition_type(Gtk::StackTransitionType::SLIDE_UP_DOWN);

        m_SidebarListBox.set_margin_start(5);
        m_SidebarListBox.signal_row_activated().connect([&](Gtk::ListBoxRow* row)
        {
            auto box = dynamic_cast<Gtk::Box*>(row->get_child());
            m_Stack.set_visible_child(box->get_name());
        });

        m_MainHBox.prepend(m_SidebarListBox);
        m_MainHBox.append(m_Stack);
        m_Stack.set_expand();

        set_child(m_MainHBox);
        add_overlay(InfoBar::_());
    }

    Gtk::ListBoxRow* RootContent::MakeSidebarItem(const Glib::RefPtr<SearchableContent>& searchable_content)
    {
        auto sidebarItemRow = Gtk::make_managed<Gtk::ListBoxRow>();
        auto sidebarRowHBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
        auto sidebarTitle = Gtk::make_managed<Gtk::Label>(searchable_content->GetTitle(), Gtk::Align::START);
        auto sidebarRowVBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 0);
        sidebarRowHBox->prepend(*sidebarTitle);
        sidebarRowHBox->append(searchable_content->GetSpinner());
        sidebarRowHBox->set_expand();

        sidebarRowVBox->set_name(searchable_content->GetTitle());
        sidebarRowVBox->prepend(*sidebarRowHBox);
        sidebarRowVBox->append(searchable_content->GetProgressBar());

        sidebarItemRow->set_child(*sidebarRowVBox);
        CssProvider::LoadProvider(*sidebarItemRow);
        sidebarItemRow->add_css_class("list_row");
        return sidebarItemRow;
    }

    void RootContent::Search(const std::string& search_text)
    {
        UIQueue::_().Push([&]() { ClearResult(); HEADER_BAR(ToggleSearching); });

        for (auto& searchEntity : m_SearchableList)
            TaskQueue::_().Push([&](const std::string& search_text) { searchEntity->Search(search_text); }, search_text);
        TaskQueue::_().Push([]()
        {
            UIQueue::_().Push([]()
            {
//                INFO_BAR(Info, LANGUAGE(search_finished));
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