//
// Created by Htrap19 on 3/22/2022.
//

#ifndef PRICECHECKER_WINDOW_H
#define PRICECHECKER_WINDOW_H

#include <gtkmm.h>
#include "RootContent.h"
#include "HeaderBar.h"

namespace PC
{
    class Window : public Gtk::Window
    {
    public:
        Window();

    private:
        HeaderBar& m_TitleBar;
        RootContent& m_RootContent;

        Glib::RefPtr<Gtk::CssProvider> m_CssProvider;
    };
}

#endif //PRICECHECKER_WINDOW_H
