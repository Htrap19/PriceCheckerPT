//
// Created by htrap19 on 4/13/22.
//

#include "SearchableContent.h"
#include "InfoBar.h"
#include "HeaderBar.h"
#include "Window.h"
//#include "utils/CssProvider.h"
#include "utils/LanguageManager.h"

namespace PC
{
    SearchableContent::SearchableContent(const std::string& name, const std::string& briefUrl)
        : m_Name(name), m_BriefUrl(briefUrl)
    {
//        CssProvider::LoadProvider(m_ListBox);
//        m_ListBox.add_css_class("padding-10");
        m_ListBox.set_selection_mode(Gtk::SelectionMode::NONE);
        m_ListBox.set_placeholder(m_EmptyWidget);
        m_ListBox.set_show_separators();

        set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        set_child(m_ListBox);
    }

    void SearchableContent::Search(const std::string& url)
    {
        HEADER_BAR(SetLoadingText, m_Name);
        INFO_BAR(Info, LANGUAGE(fetching_result_from) + " " + m_BriefUrl + "!");
        Fetch(url);
    }

    void SearchableContent::FetchCallback(CDocument& doc)
    {
        ClearProductList();

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

    void SearchableContent::PushProduct(const ProductComponent::Data& data)
    {
        std::lock_guard lock(m_ProductDataMutex);
        m_ProductsData.push_back(data);
        if (!m_ProductAppendConnection)
            m_ProductAppendConnection = Glib::signal_idle().connect(sigc::mem_fun(*this, &SearchableContent::AppendProductsOnIdle));
    }

    void SearchableContent::FetchErrCallback(const std::string& what)
    {
        INFO_BAR(Error, what);
    }

    bool SearchableContent::AppendProductsOnIdle()
    {
        std::lock_guard lock(m_ProductDataMutex);
        for (auto& productData : m_ProductsData)
        {
            try
            {
                auto& comp = m_Products.emplace_back(productData);
                m_ListBox.append(comp);
            }
            catch (std::exception& e)
            {
                FetchErrCallback(e.what());
            }
        }

        m_ProductsData.clear();
        return false; // Disconnects the signal handler
    }
}