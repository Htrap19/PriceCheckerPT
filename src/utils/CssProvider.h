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
    };
}

#endif //PRICECHECKER_CSSPROVIDER_H
