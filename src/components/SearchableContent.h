//
// Created by htrap19 on 4/13/22.
//

#ifndef PRICECHECKER_SEARCHABLECONTENT_H
#define PRICECHECKER_SEARCHABLECONTENT_H

#include <gtkmm.h>
#include "utils/Searchable.h"
#include "EmptyList.h"

namespace PC
{
    class SearchableContent : public Gtk::ScrolledWindow, public Searchable
    {
    public:
        virtual ~SearchableContent() = default;
        inline Gtk::Widget& GetWidget() override { return *this; }
        void FetchCallback(CDocument& doc) override;
        [[nodiscard]] inline const std::string& GetName() const override { return m_Name; }
        [[nodiscard]] inline const std::string& GetTitle() const override { return m_Name; }

    protected:
        explicit SearchableContent(const std::string& name);
        void FetchErrCallback(const std::string& what) override;
        void ClearProductList();

    protected:
        Gtk::ListBox m_ListBox;
        EmptyList m_EmptyWidget;

        std::string m_Name;
    };
}

#endif //PRICECHECKER_SEARCHABLECONTENT_H
