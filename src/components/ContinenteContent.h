//
// Created by Htrap19 on 3/22/2022.
//

#ifndef PRICECHECKER_CONTINENTECONTENT_H
#define PRICECHECKER_CONTINENTECONTENT_H

#include <gtkmm.h>
#include "ProductComponent.h"
#include "EmptyList.h"
#include "utils/Searchable.h"

namespace PC
{
    class ContinenteContent : public Gtk::ScrolledWindow, public Searchable
    {
    public:
        ContinenteContent();

        void Search(const std::string& search_text) override;
        inline Widget& GetWidget() override { return *this; }
        void FetchCallback(CDocument& doc) override;
        void FetchErrCallback(const std::string &what) override;

        inline const std::string& GetName() const override { return m_Name; }
        inline const std::string& GetTitle() const override { return m_Name; }

    private:
        Gtk::ListBox m_ListBox;
        EmptyList m_EmptyWidget;

        std::string m_Name = "Continente";
    };
}

#endif //PRICECHECKER_CONTINENTECONTENT_H
