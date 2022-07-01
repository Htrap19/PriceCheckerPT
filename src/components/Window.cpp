//
// Created by Htrap19 on 3/22/2022.
//

#include "Window.h"
#include "utils/LanguageManager.h"
#include "utils/AssetManager.h"

namespace PC
{
    Window::Window()
        : m_RootContent(RootContent::_()),
          m_TitleBar(HeaderBar::_()),
          m_CssProvider(Gtk::CssProvider::create())
    {
        // Load css
        auto display = get_display();
        m_CssProvider->load_from_data(ASSET(Mics, "styles"));
        Gtk::StyleContext::add_provider_for_display(display, m_CssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

        m_TitleBar.SetKeyCaptureWidget(*this);

        m_TitleBar.SetTitle(LANGUAGE(app_title));
        set_default_size(1024, 720);
        set_default_widget(m_TitleBar.GetSearchButton());

        set_titlebar(m_TitleBar);
        set_child(m_RootContent);
    }
}