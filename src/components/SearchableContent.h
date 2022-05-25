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
        inline Gtk::Spinner& GetSpinner() { return m_Spinner; }
        inline Gtk::ProgressBar& GetProgressBar() { return m_ProgressBar; }
        inline void SetTotalItemsCount(uint32_t total_item_count) { m_TotalItemCount = total_item_count; m_ProgressBar.set_fraction(0.0); }
        void Increment();
        void ClearProductList();

    protected:
        SearchableContent(const std::string& name, const std::string& briefUrl);
        void FetchErrCallback(const std::string& what) override;

    protected:
        std::list<ProductComponent> m_Products;
        Gtk::ListBox m_ListBox;
        EmptyList m_EmptyWidget;
        Gtk::Spinner m_Spinner;
        Gtk::ProgressBar m_ProgressBar;

        std::string m_Name;
        std::string m_BriefUrl;

        // Progress bar
        uint32_t m_TotalItemCount;
    };
}

#endif //PRICECHECKER_SEARCHABLECONTENT_H
