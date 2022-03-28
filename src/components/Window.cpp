//
// Created by Htrap19 on 3/22/2022.
//

#include "Window.h"
#include "RootVBox.h"

namespace ps
{
    static const std::string window_title = "Price Checker PT";

    Window::Window()
    {
        m_TitleLabel.set_label(window_title);
        m_TitleBar.set_title_widget(m_TitleLabel);
        m_TitleBar.set_show_title_buttons(true);

        set_default_size(640, 480);

        set_titlebar(m_TitleBar);
        set_child(RootVBox::_());
    }
}