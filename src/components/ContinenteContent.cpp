//
// Created by Htrap19 on 3/22/2022.
//

#include "ContinenteContent.h"
#include "InfoBar.h"
#include "utils/CssProvider.h"
#include "utils/Utils.h"
#include <Node.h>

namespace PC
{
    ContinenteContent::ContinenteContent()
    {
        CssProvider::LoadProvider(m_ListBox);
        m_ListBox.add_css_class("padding-10");
        m_ListBox.set_selection_mode(Gtk::SelectionMode::NONE);
        m_ListBox.set_placeholder(m_EmptyWidget);
        m_ListBox.set_show_separators();

        set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        set_child(m_ListBox);
    }

    void ContinenteContent::Search(const std::string& search_text)
    {
        auto productNameUrlFormat = ConvertToUrlQuery(search_text);
        auto url = std::string("https://www.continente.pt/pesquisa/?q=") + productNameUrlFormat + "&start=0";

        InfoBar::_().Info("Fetching result from www.continente.pt!");
        Fetch(url);
    }

    void ContinenteContent::FetchCallback(CDocument& doc)
    {
        for (auto& productCom : m_Products)
            m_ListBox.remove(productCom);
        m_Products.clear();

        auto selection = doc.find("div.product");
        for (size_t i = 0; i < selection.nodeNum(); i++)
        {
            try
            {
                auto node = selection.nodeAt(i);
                auto imgNode = node.find("img.ct-tile-image").nodeAt(0);

                // Product Name
                auto productName = imgNode.attribute("title");

                // Product Img
                auto productImgSrc = imgNode.attribute("data-src");

                // Product Prices
                auto priceNode = node.find("span.sales span.value").nodeAt(0);
                auto actualFormattedPrice = priceNode.childAt(1).text() + priceNode.childAt(3).text();
                Utils::RemoveEmptySpace(actualFormattedPrice);

                auto originalPriceNode = node.find("span.ct-tile--price-value");
                std::string originalPrice = "-";
                if (originalPriceNode.nodeNum() > 0)
                {
                    auto originalPriceNodeValue = originalPriceNode.nodeAt(0);
                    originalPrice = originalPriceNodeValue.childAt(2).text() + originalPriceNodeValue.childAt(3).text();
                    Utils::RemoveEmptySpace(originalPrice);
                }

                auto secondaryPriceDescNode = node.find("div.ct-tile--price-secondary");
                auto secondaryPriceDesc = secondaryPriceDescNode.nodeAt(0).childAt(1).text() + secondaryPriceDescNode.nodeAt(0).childAt(3).text();
                Utils::RemoveEmptySpace(secondaryPriceDesc);

                // Product Branding
                auto productBrand = node.find("p.ct-tile--brand").nodeAt(0).text();

                // Product Packaging
                auto productPackaging = node.find("p.ct-tile--quantity").nodeAt(0).text();

                auto& productCom = m_Products.emplace_back(
                        productName,
                        productBrand,
                        productPackaging,
                        originalPrice,
                        actualFormattedPrice,
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

    void ContinenteContent::FetchErrCallback(const std::string& what)
    {
        InfoBar::_().Error(what);
    }
}
