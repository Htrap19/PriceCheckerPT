//
// Created by htrap19 on 4/13/22.
//

#include "MiniPreco.h"
#include "InfoBar.h"
#include "utils/Utils.h"
#include <Node.h>

namespace PC
{
    MiniPreco::MiniPreco()
        : SearchableContent("MiniPreco")
    {
    }

    void MiniPreco::Search(const std::string& search_text)
    {
        auto productNameUrlFormat = ConvertToUrlQuery(search_text);
        auto url = std::string("https://lojaonline.minipreco.pt/search?text=") + productNameUrlFormat;

        InfoBar::_().Info("Fetching result from www.lojaonline.minipreco.pt!");
        Fetch(url);
    }

    void MiniPreco::FetchCallback(CDocument& doc)
    {
        ClearProductList();

        auto selection = doc.find("div.product-list__item");
        for (size_t i = 0; i < selection.nodeNum(); i++)
        {
            auto node = selection.nodeAt(i);
            auto imgNode = node.find("div.thumb").nodeAt(0).childAt(1);

            // Product Name
            auto productName = imgNode.attribute("title");

            // Product Image
            auto productImgSrc = imgNode.attribute("data-original");

            // Product Price
            auto priceNode = node.find("div.price_container").nodeAt(0);
            std::string originalPrice, actualPrice;

            auto priceNodeChild = priceNode.childAt(1);
            if (priceNodeChild.childNum() >= 1 && priceNodeChild.childNum() < 3)
                actualPrice = priceNodeChild.childAt(0).text();
            else
            {
                originalPrice = priceNodeChild.childAt(1).text();
                actualPrice = priceNodeChild.childAt(2).text();
            }
            Utils::RemoveEmptySpace(originalPrice);
            Utils::RemoveEmptySpace(actualPrice);

            auto secondaryPriceDescNode = priceNode.childAt(3);
            std::string secondaryPriceDesc;
            if (secondaryPriceDescNode.childNum() >= 1 && secondaryPriceDescNode.childNum() < 3)
                secondaryPriceDesc = secondaryPriceDescNode.childAt(0).text();
            else
                secondaryPriceDesc = secondaryPriceDescNode.childAt(2).text();
            Utils::RemoveEmptySpace(secondaryPriceDesc);

            auto& comp = m_Products.emplace_back(
                    productName,
                    "",
                    "",
                    originalPrice,
                    actualPrice,
                    secondaryPriceDesc,
                    productImgSrc);
            m_ListBox.append(comp);
        }

        SearchableContent::FetchCallback(doc);
    }
}
