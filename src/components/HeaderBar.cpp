//
// Created by htrap19 on 4/4/22.
//

#include "HeaderBar.h"
#include "RootContent.h"
#include "utils/TaskQueue.h"
#include "utils/FileCacheManager.h"
#include "InfoBar.h"

namespace PC
{
    HeaderBar::HeaderBar(Gtk::Widget& key_capture_widget)
        : m_SearchButton("_Search", true)
    {
        m_SearchButton.signal_clicked().connect(sigc::mem_fun(*this, &HeaderBar::handle_search));
        m_SearchEntry.property_activates_default().set_value(true);
        m_SearchEntry.set_key_capture_widget(key_capture_widget);

        m_SettingsButton.set_icon_name("open-menu");
        m_SettingsButton.set_popover(m_SettingsMenu);

        m_SettingsActionGroup = Gio::SimpleActionGroup::create();
        m_SettingsActionGroup->add_action("clear_cache", sigc::mem_fun(*this, &HeaderBar::ClearCache));

        auto utilsSection = Gio::Menu::create();
        utilsSection->append_item(Gio::MenuItem::create("Compare", "settings.compare"));

        auto settingsSection = Gio::Menu::create();
        settingsSection->append_item(Gio::MenuItem::create("Clear Cache", "settings.clear_cache"));
        settingsSection->append_item(Gio::MenuItem::create("About", "settings.about"));

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
        InfoBar::_().Ask("Do want to clear the cache ?", &FileCacheManager::ClearCache, &FileCacheManager::_());
    }
}