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
        void Search(const std::string& url) override; // same name but different logic implementation
        void FetchCallback(CDocument& doc) override;
        virtual void ParseSearchableContent(CDocument& doc) = 0;
        [[nodiscard]] inline const std::string& GetName() const override { return m_Name; }
        [[nodiscard]] inline const std::string& GetTitle() const override { return m_Name; }
        inline Gtk::ListBox& GetListBox() { return m_ListBox; }
        inline const Gtk::ListBox& GetListBox() const { return m_ListBox; }
        inline Gtk::Spinner& GetSpinner() { return m_Spinner; }
        inline const Gtk::Spinner& GetSpinner() const { return m_Spinner; }
        void ClearProductList();

    protected:
        SearchableContent(const std::string& name, const std::string& briefUrl);
        void FetchErrCallback(const std::string& what) override;

    protected:
        std::list<ProductComponent> m_Products;
        Gtk::ListBox m_ListBox;
        EmptyList m_EmptyWidget;
        Gtk::Spinner m_Spinner;

        std::string m_Name;
        std::string m_BriefUrl;
    };
}

#endif //PRICECHECKER_SEARCHABLECONTENT_H
