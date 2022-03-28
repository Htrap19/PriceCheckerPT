//
// Created by Htrap19 on 3/22/2022.
//

#ifndef PRICECHECKER_CONTENTVBOX_H
#define PRICECHECKER_CONTENTVBOX_H

#include <gtkmm.h>
#include "utils/Searchable.h"

namespace ps
{
    class ContentVBox : public Gtk::Box
    {
    public:
        ContentVBox();

        void Search(const std::string& search_text);

    private:
        Gtk::Paned m_Paned;

        std::vector<Glib::RefPtr<Searchable>> m_SearchableList;
    };
}

#endif //PRICECHECKER_CONTENTVBOX_H
