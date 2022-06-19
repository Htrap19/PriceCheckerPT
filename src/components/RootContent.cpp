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
#include "components/stores/RecheioContent.h"
#include "components/CompareComponent.h"
#include "utils/TaskQueue.h"
#include "utils/LanguageManager.h"
#include "utils/ConfigManager.h"
#include "utils/UIQueue.h"
#include "utils/CssProvider.h"

extern Glib::RefPtr<Gtk::Application> app;

namespace PC
{
    static std::unique_ptr<Gtk::FileChooserDialog> s_FileChooserDialog = nullptr;

    RootContent::RootContent()
        : m_MainHBox(Gtk::Orientation::HORIZONTAL, 10)
    {
        m_SearchableList.emplace_back(std::make_shared<ContinenteContent>());
        m_SearchableList.emplace_back(std::make_shared<AuchanContent>());
        m_SearchableList.emplace_back(std::make_shared<MiniprecoContent>());
        m_SearchableList.emplace_back(std::make_shared<ElcorteinglesContent>());
        m_SearchableList.emplace_back(std::make_shared<SparContent>());
        m_SearchableList.emplace_back(std::make_shared<RecheioContent>());

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
        if (searchable_content->UseCookies())
        {
            auto cookiesImage = Gtk::make_managed<Gtk::Image>(ASSET(Image, "cookies"));
            auto clicker = Gtk::GestureClick::create();
            clicker->signal_released().connect([&](int, double, double)
            {
                if (s_FileChooserDialog)
                {
                    s_FileChooserDialog->show();
                    return;
                }

                auto window = app->get_active_window();
                s_FileChooserDialog = std::make_unique<Gtk::FileChooserDialog>(*window,"Select cookies file", Gtk::FileChooser::Action::OPEN, true);
                s_FileChooserDialog->set_transient_for(*window);
                s_FileChooserDialog->set_modal();
                s_FileChooserDialog->add_button("Select", Gtk::ResponseType::OK);
                s_FileChooserDialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
                s_FileChooserDialog->signal_response().connect([&](int response_id)
                {
                    s_FileChooserDialog->hide();
                    if (response_id == Gtk::ResponseType::OK)
                    {
                        auto filePath = s_FileChooserDialog->get_file()->get_path();
                        CONFIG(SetCookiesPath, searchable_content->GetName(), filePath);
                    }
                });
                s_FileChooserDialog->signal_close_request().connect([]() -> bool
                {
                    s_FileChooserDialog->hide();
                    return true;
                }, false);
            });
            cookiesImage->add_controller(clicker);
            sidebarRowHBox->append(*cookiesImage);
        }
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
        ToggleSearching();

        for (auto& searchEntity : m_SearchableList)
            TaskQueue::_().Push([&](const std::string& search_text) { searchEntity->Search(search_text); }, search_text);

        ToggleSearching(false);
    }

    void RootContent::ToggleSearching(bool toggle)
    {
        if (toggle)
        {
            UI([&]() { ClearResult(); HEADER_BAR(ToggleSearching); });
            return;
        }

        TaskQueue::_().Push([&]()
        {
            while (std::any_of(m_SearchableList.begin(), m_SearchableList.end(), [](const Glib::RefPtr<SearchableContent>& searchEntity) { return searchEntity->IsRunning(); }));
            UI([]()
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

    void RootContent::StopSearch()
    {
        for (auto& searchEntity : m_SearchableList)
            searchEntity->SetIsRunning(false);
    }
}