//
// Created by htrap19 on 4/14/22.
//

#include "ElcorteinglesContent.h"
#include "utils/UIQueue.h"
#include <Node.h>

namespace PC
{

    ElcorteinglesContent::ElcorteinglesContent()
        : SearchableContent("Elcorteingles", "www.elcorteingles.pt")
    {
    }

    void ElcorteinglesContent::Search(const std::string& search_text)
    {
        auto productNameUrlFormat = ConvertToUrlQuery(search_text);
        auto url = std::string("https://www.elcorteingles.pt/supermercado/pesquisar/?term=") + productNameUrlFormat + "&search=text";

        SearchableContent::Search(url);
    }

    void ElcorteinglesContent::ParseSearchableContent(CDocument& doc)
    {
        auto selection = doc.find("div.product_tile");
        SetTotalItemsCount(selection.nodeNum());
        for (size_t i = 0; i < selection.nodeNum(); i++)
        {
            try
            {
                auto node = selection.nodeAt(i);
                if (!node.valid() || node.childNum() == 0)
                    continue;

                auto imgNodeSelection = node.find("a.js-product-link");
                if (imgNodeSelection.nodeNum() == 0 || imgNodeSelection.nodeAt(0).childNum() == 0)
                    continue;

                auto imgNode = imgNodeSelection.nodeAt(0).childAt(0);

                // Product Name
                auto productName = imgNode.attribute("title");

                // Product Image
                auto productImgSrc = "https:" + imgNode.attribute("src");

                // Product Prices
                auto priceNodeSelection = node.find("div.product_tile-prices");
                if (priceNodeSelection.nodeNum() <= 0 || priceNodeSelection.nodeAt(0).childNum() <= 0)
                    continue;

                auto priceNode = priceNodeSelection.nodeAt(0).childAt(0);
                std::string actualPrice, originalPrice, secondaryPriceDesc;
                if (priceNode.childNum() >= 2 && priceNode.childNum() < 6)
                {
                    actualPrice = priceNode.childAt(0).text();
                    secondaryPriceDesc = priceNode.childAt(1).text();
                }
                else
                {
                    if (priceNode.childNum() > 1)
                    {
                        originalPrice = priceNode.childAt(0).text();
                        actualPrice = priceNode.childAt(2).text();
                        secondaryPriceDesc = priceNode.childAt(3).text();
                    }
                    else
                        actualPrice = priceNode.childAt(0).text();
                }
                Utils::RemoveEmptySpace(originalPrice);
                Utils::RemoveEmptySpace(actualPrice);
                Utils::RemoveEmptySpace(secondaryPriceDesc);

                auto& comp = m_Products.emplace_back(
                            productName,
                            "",
                            "",
                            originalPrice,
                            actualPrice,
                            secondaryPriceDesc,
                            productImgSrc);
                UIQueue::_().Push([&]()
                {
                    comp.AddToSizeGroup();
                    m_ListBox.append(comp);
                    Increment(); // Progressbar
                });
            }
            catch (std::exception& e)
            {
#ifdef PC_DEBUG
                std::cout << e.what() << std::endl;
#endif
                SearchableContent::FetchErrCallback(e.what());
            }
        }
    }
}