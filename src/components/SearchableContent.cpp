//
// Created by htrap19 on 4/13/22.
//

#include "SearchableContent.h"
#include "InfoBar.h"
#include "utils/CssProvider.h"

namespace PC
{
    SearchableContent::SearchableContent(const std::string& name)
        : m_Name(name)
    {
        CssProvider::LoadProvider(m_ListBox);
        m_ListBox.add_css_class("padding-10");
        m_ListBox.set_selection_mode(Gtk::SelectionMode::NONE);
        m_ListBox.set_placeholder(m_EmptyWidget);
        m_ListBox.set_show_separators();

        set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        set_child(m_ListBox);
    }

    void SearchableContent::FetchCallback(CDocument& doc)
    {
        if (m_Products.empty())
            m_EmptyWidget.SetLabel("Product Not Found!");
    }

    void SearchableContent::FetchErrCallback(const std::string& what)
    {
        InfoBar::_().Error(what);
    }

    void SearchableContent::ClearProductList()
    {
        for (auto& productCom : m_Products)
            m_ListBox.remove(productCom);
        m_Products.clear();
    }
}