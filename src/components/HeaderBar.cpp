//
// Created by htrap19 on 4/4/22.
//

#include "HeaderBar.h"
#include "RootContent.h"
#include "utils/TaskQueue.h"
#include "utils/FileCacheManager.h"
#include "utils/LanguageManager.h"
#include "utils/ConfigManager.h"
#include "InfoBar.h"

namespace PC
{
    HeaderBar::HeaderBar(Gtk::Widget& key_capture_widget)
        : m_SearchButton("_" + LANGUAGE(search_button_text), true)
    {
        m_SearchButton.signal_clicked().connect(sigc::mem_fun(*this, &HeaderBar::handle_search));
        m_SearchEntry.property_activates_default().set_value(true);
        m_SearchEntry.set_key_capture_widget(key_capture_widget);

        m_SettingsButton.set_icon_name("open-menu");
        m_SettingsButton.set_popover(m_SettingsMenu);

        m_SettingsActionGroup = Gio::SimpleActionGroup::create();
        m_SettingsActionGroup->add_action("clear_cache", sigc::mem_fun(*this, &HeaderBar::ClearCache));;

        auto utilsSection = Gio::Menu::create();
        utilsSection->append_item(Gio::MenuItem::create(LANGUAGE(compare), "settings.compare"));

        auto settingsSection = Gio::Menu::create();
        auto languageMenuItem = Gio::MenuItem::create(LANGUAGE(language), "");
        auto languageSelectionMenu = Gio::Menu::create();
        for (auto& lang : LANG(GetLangPacks))
        {
            auto action_name = "lang_" + lang;
            m_SettingsActionGroup->add_action(action_name, [lang]()
            {
                CONFIG(SetLang, lang);
            });
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

        set_title_widget(m_TitleLabel);
        set_show_title_buttons(true);
        pack_start(m_SearchEntry);
        pack_start(m_SearchButton);
        pack_end(m_SettingsButton);
        pack_end(m_Spinner);
    }

    void HeaderBar::ToggleSearching(bool toggle)
    {
        m_SearchButton.set_sensitive(!toggle);
        m_SearchEntry.set_sensitive(!toggle);
        (toggle ? m_Spinner.start() : m_Spinner.stop());
        m_SettingsActionGroup->action_enabled_changed("clear_cache", !toggle);
    }

    void HeaderBar::handle_search()
    {
        auto search_text = m_SearchEntry.get_text();
        if (!search_text.empty())
            TaskQueue::_().Push(&RootContent::Search, &RootContent::_(), search_text);
    }

    void HeaderBar::ClearCache()
    {
        InfoBar::_().Ask(LANGUAGE(clear_cache_question), &FileCacheManager::ClearCache, &FileCacheManager::_());
    }
}