//
// Created by Htrap19 on 3/22/2022.
//

#include "Window.h"
#include "utils/LanguageManager.h"

namespace PC
{
    static const std::string s_WindowTitle = "Price Checker PT";
    bool Window::Closed = false;

    Window::Window()
        : m_RootContent(RootContent::_()),
          m_TitleBar(HeaderBar::_())
    {
        m_TitleBar.SetKeyCaptureWidget(*this);

        m_TitleBar.SetTitle(LANGUAGE(app_title));
        set_default_size(640, 480);
        set_default_widget(m_TitleBar.GetSearchButton());

        set_titlebar(m_TitleBar);
        set_child(m_RootContent);
    }

    Window::~Window()
    {
        Closed = false;
    }
}