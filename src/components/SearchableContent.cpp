//
// Created by htrap19 on 4/13/22.
//

#include "SearchableContent.h"
#include "components/InfoBar.h"
#include "utils/CssProvider.h"
#include "utils/LanguageManager.h"
#include "utils/ConfigManager.h"
#include "utils/UIQueue.h"

namespace PC
{
    SearchableContent::SearchableContent(const std::string& name, bool use_cookies)
        : m_Name(name), m_UseCookies(use_cookies)
    {
        m_Spinner.set_expand();
        m_Spinner.set_halign(Gtk::Align::END);

        CssProvider::LoadProvider(m_ListBox);
        m_ListBox.add_css_class("padding-10");
        m_ListBox.set_selection_mode(Gtk::SelectionMode::MULTIPLE);
        m_ListBox.set_placeholder(m_EmptyWidget);
        m_ListBox.set_show_separators();
        m_ListBox.set_activate_on_single_click(false);

        set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        set_child(m_ListBox);
    }

    void SearchableContent::Search(const std::string& url)
    {
        SetIsRunning(true);
        UI([&](){ m_Spinner.start(); });
        Fetch(url, (m_UseCookies ? CONFIG(GetCookiesPath, GetName()) : ""));
    }

    void SearchableContent::FetchCallback(CDocument& doc)
    {
        ParseSearchableContent(doc);

        if (m_Products.empty())
            m_EmptyWidget.SetLabel(LANGUAGE(product_not_found));
        m_Spinner.stop();
        SetIsRunning(false);
    }

    void SearchableContent::Increment()
    {
        if (m_TotalItemCount == 0)
            return;

        auto fraction = m_ProgressBar.get_fraction();
        m_ProgressBar.set_fraction(fraction + (1.0f / static_cast<float>(m_TotalItemCount)));
    }

    void SearchableContent::ClearProductList()
    {
        for (auto& productCom : m_Products)
            m_ListBox.remove(productCom);
        m_Products.clear();
        SetTotalItemsCount(0);
    }

    void SearchableContent::FetchErrCallback(const std::string& what)
    {
        UI([&](const std::string& what)
        {
            INFO_BAR(Error, what);
            m_Spinner.stop();
            SetIsRunning(false);
        }, what);
    }
}