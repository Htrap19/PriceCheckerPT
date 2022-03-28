//
// Created by Htrap19 on 3/22/2022.
//

#ifndef PRICECHECKER_AUCHANCONTENT_H
#define PRICECHECKER_AUCHANCONTENT_H

#include <gtkmm.h>
#include "ProductComponent.h"
#include "utils/Searchable.h"

namespace ps
{
    class AuchanContent : public Gtk::ScrolledWindow, public Searchable
    {
    public:
        AuchanContent();

        void Search(const std::string& search_text) override;
        inline Widget& GetWidget() override { return *this; }
        void FetchCallback(CDocument& doc) override;
        void FetchErrCallback(const std::string& what) override;

    private:
        Gtk::FlowBox m_FlowBox;
    };
}

#endif //PRICECHECKER_AUCHANCONTENT_H
