//
// Created by htrap19 on 4/13/22.
//

#include "MiniprecoContent.h"
#include "utils/UIQueue.h"
#include "Node.h"

namespace PC
{
    MiniprecoContent::MiniprecoContent()
        : SearchableContent("Minipreco")
    {
    }

    void MiniprecoContent::Search(const std::string& search_text)
    {
        auto productNameUrlFormat = ConvertToUrlQuery(search_text);
        auto url = std::string("https://www.minipreco.pt/search?text=") + productNameUrlFormat;

        SearchableContent::Search(url);
    }

    void MiniprecoContent::ParseSearchableContent(CDocument& doc)
    {
        auto selection = doc.find("div.product-list__item");
        SetTotalItemsCount(selection.nodeNum());
        for (size_t i = 0; (i < selection.nodeNum() && IsRunning()); i++)
        {
            try
            {
                auto node = selection.nodeAt(i);
                if (!node.valid() || node.childNum() == 0)
                    continue;

                auto imgNodeSelection = node.find("div.thumb");
                if (imgNodeSelection.nodeNum() == 0 || imgNodeSelection.nodeAt(0).childNum() == 0)
                    continue;
                auto imgNode = imgNodeSelection.nodeAt(0).childAt(1);

                // Product Name
                auto productName = imgNode.attribute("title");

                // Product Image
                auto productImgSrc = imgNode.attribute("data-original");

                // Product Price
                auto priceNodeSelection = node.find("div.price_container");
                if (priceNodeSelection.nodeNum() == 0 || priceNodeSelection.nodeAt(0).childNum() == 0)
                    continue;
                auto priceNode = priceNodeSelection.nodeAt(0);
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
                UI([&]()
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
