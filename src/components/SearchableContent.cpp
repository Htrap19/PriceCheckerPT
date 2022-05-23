//
// Created by htrap19 on 4/13/22.
//

#include "SearchableContent.h"
#include "InfoBar.h"
#include "HeaderBar.h"
//#include "utils/CssProvider.h"
#include "utils/LanguageManager.h"
#include "utils/UIQueue.h"

namespace PC
{
    SearchableContent::SearchableContent(const std::string& name, const std::string& briefUrl)
        : m_Name(name), m_BriefUrl(briefUrl)
    {
//        CssProvider::LoadProvider(m_ListBox);
//        m_ListBox.add_css_class("padding-10");
        m_ListBox.set_selection_mode(Gtk::SelectionMode::MULTIPLE);
        m_ListBox.set_placeholder(m_EmptyWidget);
        m_ListBox.set_show_separators();
        m_ListBox.set_activate_on_single_click();

        set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        set_child(m_ListBox);
    }

    void SearchableContent::Search(const std::string& url)
    {
        UIQueue::_().Push([&]()
        {
            HEADER_BAR(SetLoadingText, m_Name);
            INFO_BAR(Info, LANGUAGE(fetching_result_from) + " " + m_BriefUrl + "!");
        });
        Fetch(url);
    }

    void SearchableContent::FetchCallback(CDocument& doc)
    {
        ParseSearchableContent(doc);

        if (m_Products.empty())
            m_EmptyWidget.SetLabel(LANGUAGE(product_not_found));
    }

    void SearchableContent::ClearProductList()
    {
        for (auto& productCom : m_Products)
            m_ListBox.remove(productCom);
        m_Products.clear();
    }

    void SearchableContent::FetchErrCallback(const std::string& what)
    {
        INFO_BAR(Error, what);
    }
}