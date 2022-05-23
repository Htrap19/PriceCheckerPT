//
// Created by htrap19 on 5/23/22.
//

#include "CompareComponent.h"
#include "components/SearchableContent.h"
#include "utils/LanguageManager.h"

namespace PC
{
    CompareComponent::CompareComponent()
        : m_TreeModel(Gtk::TreeStore::create(m_Columns)),
        m_TreeView(m_TreeModel)
    {
        AppendCol(LANGUAGE(name), m_Columns.m_ColName);
        AppendCol(LANGUAGE(price_desc), m_Columns.m_ColPriceDesc);
        AppendCol(LANGUAGE(original_price), m_Columns.m_ColOriginalPrice);
        AppendCol(LANGUAGE(actual_price), m_Columns.m_ColActualPrice);
        m_TreeView.set_headers_visible();
        m_TreeView.set_reorderable();

        set_expand();
        set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        set_child(m_TreeView);
    }

    Gtk::TreeRow CompareComponent::AppendMain(const Glib::ustring& name)
    {
        auto row = *m_TreeModel->append();
        row[m_Columns.m_ColName] = name;
        return row;
    }

    Gtk::TreeRow CompareComponent::AppendChild(Gtk::TreeRow& main_row, const Glib::ustring& name, const Glib::ustring& price_desc, const Glib::ustring& original_price, const Glib::ustring& actual_price)
    {
        auto childRow = *m_TreeModel->append(main_row.children());
        childRow[m_Columns.m_ColName] = name;
        childRow[m_Columns.m_ColPriceDesc] = price_desc;
        childRow[m_Columns.m_ColOriginalPrice] = original_price;
        childRow[m_Columns.m_ColActualPrice] = actual_price;
        return childRow;
    }

    void CompareComponent::SetSearchableContentList(const std::list<Glib::RefPtr<SearchableContent>>& searchable_content_list)
    {
        m_TreeModel->clear();
        for (auto& searchable_content : searchable_content_list)
        {
            auto main_row = AppendMain(searchable_content->GetTitle());
            auto& products = searchable_content->GetListBox();
            products.selected_foreach([&](Gtk::ListBoxRow* row)
            {
                auto productComponent = dynamic_cast<ProductComponent*>(row);
                AppendChild(main_row,
                            productComponent->GetProductName(),
                            productComponent->GetProductSecondaryPriceDesc(),
                            productComponent->GetProductOriginalPrice(),
                            productComponent->GetProductActualPrice());
            });
        }
        m_TreeView.expand_all();
    }
}