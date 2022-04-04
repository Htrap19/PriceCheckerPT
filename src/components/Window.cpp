//
// Created by Htrap19 on 3/22/2022.
//

#include "Window.h"
//#include "RootVBox.h"

namespace PC
{
    static const std::string s_WindowTitle = "Price Checker PT";

    Window::Window()
        : m_RootContent(RootContent::_()),
          m_TitleBar(HeaderBar::_())
    {
        m_TitleBar.SetTitle(s_WindowTitle);
        set_default_size(640, 480);

        set_titlebar(m_TitleBar);
//        set_child(RootVBox::_());
        set_child(m_RootContent);
    }
}