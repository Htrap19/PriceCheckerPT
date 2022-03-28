//
// Created by Htrap19 on 3/22/2022.
//

#ifndef PRICECHECKER_CONTINENTECONTENT_H
#define PRICECHECKER_CONTINENTECONTENT_H

#include <gtkmm.h>
#include "ProductComponent.h"
#include "utils/Searchable.h"

namespace ps
{
    class ContinenteContent : public Gtk::ScrolledWindow, public Searchable
    {
    public:
        ContinenteContent();

        void Search(const std::string& search_text) override;
        inline Widget& GetWidget() override { return *this; }
        void FetchCallback(CDocument& doc) override;
        void FetchErrCallback(const std::string &what) override;

    private:
        Gtk::FlowBox m_FlowBox;
    };
}

#endif //PRICECHECKER_CONTINENTECONTENT_H
