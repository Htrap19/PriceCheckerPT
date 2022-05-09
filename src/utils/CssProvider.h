//
// Created by htrap19 on 4/3/22.
//

#ifndef PRICECHECKER_CSSPROVIDER_H
#define PRICECHECKER_CSSPROVIDER_H

#include <gtkmm.h>

namespace PC
{
    class CssProvider
    {
    public:
        static void LoadProvider(Gtk::Widget& widget);

    private:
        static Glib::RefPtr<Gtk::CssProvider> s_CssProvider;
        static bool s_LoadCssFile;
    };
}

#endif //PRICECHECKER_CSSPROVIDER_H
