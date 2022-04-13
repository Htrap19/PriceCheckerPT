//
// Created by Htrap19 on 3/22/2022.
//

#include "AuchanContent.h"
#include "InfoBar.h"
#include "Node.h"
#include "utils/CssProvider.h"
#include "utils/Utils.h"

namespace PC
{
    AuchanContent::AuchanContent()
    {
        CssProvider::LoadProvider(m_ListBox);
        m_ListBox.add_css_class("padding-10");
        m_ListBox.set_selection_mode(Gtk::SelectionMode::NONE);
        m_ListBox.set_placeholder(m_EmptyWidget);
        m_ListBox.set_show_separators();

        set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        set_child(m_ListBox);
    }

    void AuchanContent::Search(const std::string& search_text)
    {
        auto productNameUrlFormat = ConvertToUrlQuery(search_text);
        auto url = std::string("https://www.auchan.pt/pt/pesquisa?q=") + productNameUrlFormat + "&search-button=&lang=pt_PT";

        InfoBar::_().Info("Fetching result from www.auchan.pt!");
        Fetch(url);
    }

    void AuchanContent::FetchCallback(CDocument& doc)
    {
        for (auto& productCom : m_Products)
            m_ListBox.remove(productCom);
        m_Products.clear();

        auto selection = doc.find("div.auc-product");
        for (size_t i = 0; i < selection.nodeNum(); i++)
        {
            try
            {
                auto node = selection.nodeAt(i);
                auto imgNode = node.find("img.tile-image").nodeAt(0);

                // Product Name
                auto productName = imgNode.attribute("title");

                // Product Image
                auto productImgSrc = imgNode.attribute("data-src");

                // Product Price
                auto priceNode = node.find("span.sales").nodeAt(0);
                auto price = priceNode.childAt(1).text();
                Utils::RemoveEmptySpace(price);

                auto originalPriceNode = node.find("span.strike-through");
                std::string originalPrice = "-";
                if (originalPriceNode.nodeNum() > 0)
                    originalPrice = originalPriceNode.nodeAt(0).childAt(1).childAt(2).text();
                Utils::RemoveEmptySpace(originalPrice);

                auto secondaryPriceDescNode = node.find("div.auc-measures");
                auto secondaryPriceDesc = secondaryPriceDescNode.nodeAt(0).text();

                auto& productCom = m_Products.emplace_back(
                        productName,
                        "",
                        "",
                        originalPrice,
                        price,
                        secondaryPriceDesc,
                        productImgSrc);
                m_ListBox.append(productCom);
            }
            catch(std::exception& e)
            {
#ifdef PC_DEBUG
                std::cout << e.what() << std::endl;
#endif
                FetchErrCallback(e.what());
            }
        }

        if (m_Products.empty())
            m_EmptyWidget.SetLabel("Product not found!");
    }

    void AuchanContent::FetchErrCallback(const std::string& what)
    {
        InfoBar::_().Error(what);
    }
}