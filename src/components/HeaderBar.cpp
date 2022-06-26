//
// Created by htrap19 on 4/4/22.
//

#include "HeaderBar.h"
#include "components/RootContent.h"
#include "components/InfoBar.h"
#include "utils/UIQueue.h"
#include "utils/FileCacheManager.h"
#include "utils/LanguageManager.h"
#include "utils/ConfigManager.h"

namespace PC
{
    HeaderBar::HeaderBar()
        : m_SearchButton("_" + LANGUAGE(search_button_text), true)
    {
        m_SearchButton.signal_clicked().connect(sigc::mem_fun(*this, &HeaderBar::handle_search));
        m_SearchEntry.property_activates_default().set_value(true);

        m_SettingsButton.set_icon_name("open-menu");
        m_SettingsButton.set_popover(m_SettingsMenu);

        m_SettingsActionGroup = Gio::SimpleActionGroup::create();
        m_SettingsActionGroup->add_action("clear_cache", sigc::mem_fun(*this, &HeaderBar::ClearCache));;
        m_SettingsActionGroup->add_action("clear_result", sigc::mem_fun(RootContent::_(), &RootContent::ClearResult));
        m_SettingsActionGroup->add_action("compare", []()
        { RootContent::_().NavigateToCompare(); });
        m_SettingsActionGroup->add_action("add_to_watch_list", []()
        { RootContent::_().AddToWatchList(); });
        m_SettingsActionGroup->add_action("watch_list", []()
        { RootContent::_().NavigateToWatchList(); });

        auto utilsSection = Gio::Menu::create();
        utilsSection->append_item(Gio::MenuItem::create(LANGUAGE(compare), "settings.compare"));
        utilsSection->append_item(Gio::MenuItem::create(LANGUAGE(clear_result), "settings.clear_result"));
        utilsSection->append_item(Gio::MenuItem::create(LANGUAGE(add_to_watchlist), "settings.add_to_watch_list"));
        utilsSection->append_item(Gio::MenuItem::create(LANGUAGE(watchlist), "settings.watch_list"));

        auto settingsSection = Gio::Menu::create();
        auto languageMenuItem = Gio::MenuItem::create(LANGUAGE(language), "");
        auto languageSelectionMenu = Gio::Menu::create();
        for (auto& lang : LANG(GetLangPacks))
        {
            auto action_name = "lang_" + lang;
            m_SettingsActionGroup->add_action(action_name, [lang]() { CONFIG(SetLang, lang); });
            languageSelectionMenu->append_item(Gio::MenuItem::create(lang + " - " + LANG(GetFullNameOfLang, lang), "settings." + action_name));
        }
        languageMenuItem->set_submenu(languageSelectionMenu);
        settingsSection->append_item(languageMenuItem);
        settingsSection->append_item(Gio::MenuItem::create(LANGUAGE(clear_cache), "settings.clear_cache"));
        settingsSection->append_item(Gio::MenuItem::create(LANGUAGE(about), "settings.about"));

        auto settingsMenuModel = Gio::Menu::create();
        settingsMenuModel->append_section(utilsSection);
        settingsMenuModel->append_section(settingsSection);

        m_SettingsMenu.set_menu_model(settingsMenuModel);
        m_SettingsMenu.set_autohide();
        m_SettingsMenu.set_position(Gtk::PositionType::BOTTOM);
        m_SettingsMenu.insert_action_group("settings", m_SettingsActionGroup);

        m_StopSearchButton.set_icon_name("media-playback-stop");
        m_StopSearchButton.set_sensitive(false);
        m_StopSearchButton.signal_clicked().connect(sigc::mem_fun(*this, &HeaderBar::handle_stop_search));

        set_title_widget(m_TitleLabel);
        set_show_title_buttons(true);
        pack_start(m_SearchEntry);
        pack_start(m_SearchButton);
        pack_start(m_StopSearchButton);
        pack_end(m_SettingsButton);
    }

    void HeaderBar::ToggleSearching(bool toggle)
    {
        m_SearchButton.set_sensitive(!toggle);
        m_SearchEntry.set_sensitive(!toggle);
        m_StopSearchButton.set_sensitive(toggle);
        m_SettingsActionGroup->action_enabled_changed("clear_cache", !toggle);
        m_SettingsActionGroup->action_enabled_changed("clear_result", !toggle);
        m_SettingsActionGroup->action_enabled_changed("compare", !toggle);
        m_SettingsActionGroup->action_enabled_changed("add_to_watch_list", !toggle);
    }

    void HeaderBar::handle_search()
    {
        auto search_text = m_SearchEntry.get_text();
        if (!search_text.empty() && (search_text != m_LastSearchedText || !RootContent::_().IsCompleted()))
            RootContent::_().Search(search_text);
        m_LastSearchedText = search_text;
    }

    void HeaderBar::handle_stop_search()
    {
        UI([]() { INFO_BAR(Info, LANGUAGE(stop_text) + "..."); });
        m_StopSearchButton.set_sensitive(false);
        RootContent::_().StopSearch();
    }

    void HeaderBar::ClearCache()
    {
        UI([]() { INFO_BAR(Ask, LANGUAGE(clear_cache_question), &FileCacheManager::ClearCache); });
    }
}