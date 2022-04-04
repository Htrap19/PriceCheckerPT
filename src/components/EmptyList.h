//
// Created by htrap19 on 4/4/22.
//

#ifndef PRICECHECKER_EMPTYLIST_H
#define PRICECHECKER_EMPTYLIST_H

#include <gtkmm.h>

namespace PC
{
    class EmptyList : public Gtk::Box
    {
    public:
        explicit EmptyList(const std::string& nothing_label = "Nothing Todo");

        inline void SetLabel(const std::string& label) { m_Nothing.set_label(label); }

    private:
        Gtk::Image m_OpenBoxImage;
        Gtk::Label m_Nothing;
    };

}

#endif //PRICECHECKER_EMPTYLIST_H
