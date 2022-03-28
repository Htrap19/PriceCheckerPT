//
// Created by Htrap19 on 3/22/2022.
//

#ifndef PRICECHECKER_WINDOW_H
#define PRICECHECKER_WINDOW_H

#include <gtkmm.h>

namespace ps
{
    class Window : public Gtk::Window
    {
    public:
        Window();

    private:
        Gtk::Label m_TitleLabel;
        Gtk::HeaderBar m_TitleBar;
    };
}

#endif //PRICECHECKER_WINDOW_H
