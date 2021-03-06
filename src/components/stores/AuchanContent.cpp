//
// Created by Htrap19 on 3/22/2022.
//

#include "AuchanContent.h"
#include "utils/UIQueue.h"
#include "components/WatchListComponent.h"
#include <Node.h>

namespace PC
{
    AuchanContent::AuchanContent()
        : SearchableContent("Auchan")
    {
    }

    void AuchanContent::Search(const std::string& search_text)
    {
        auto productNameUrlFormat = ConvertToUrlQuery(search_text);
        auto url = std::string("https://www.auchan.pt/pt/pesquisa?q=") + productNameUrlFormat + "&search-button=&lang=pt_PT";

        SearchableContent::Search(url);
    }

    void AuchanContent::ParseSearchableContent(CDocument& doc)
    {
        auto selection = doc.find("div.auc-product");
        SetTotalItemsCount(selection.nodeNum());
        for (size_t i = 0; (i < selection.nodeNum() && IsRunning()); i++)
        {
            try
            {
                auto node = selection.nodeAt(i);
                if (!node.valid() || node.childNum() == 0)
                    continue;

                auto imgNodeSelection = node.find("img.tile-image");
                if (imgNodeSelection.nodeNum() == 0)
                    continue;

                auto imgNode = imgNodeSelection.nodeAt(0);

                // Product Name
                auto productName = imgNode.attribute("title");

                // Product Image
                auto productImgSrc = imgNode.attribute("data-src");

                // Product Price
                auto priceNodeSelection = node.find("span.sales");
                if (priceNodeSelection.nodeNum() == 0 || priceNodeSelection.nodeAt(0).childNum() == 0)
                    continue;
                auto priceNode = priceNodeSelection.nodeAt(0);
                auto price = priceNode.childAt(1).text();
                Utils::RemoveEmptySpace(price);

                auto originalPriceNode = node.find("span.strike-through");
                std::string originalPrice = "-";
                if (originalPriceNode.nodeNum() > 0)
                    originalPrice = originalPriceNode.nodeAt(0).childAt(2).text();
                Utils::RemoveEmptySpace(originalPrice);

                auto secondaryPriceDescSelection = node.find("div.auc-measures");
                if (secondaryPriceDescSelection.nodeNum() == 0)
                    continue;
                auto secondaryPriceDesc = secondaryPriceDescSelection.nodeAt(0).text();
                Utils::RemoveEmptySpace(secondaryPriceDesc);

                auto& comp = m_Products.emplace_back(
                            productName,
                            "", "",
                            originalPrice,
                            price,
                            secondaryPriceDesc,
                            productImgSrc);
                UI([&]()
                {
                    comp.AddToSizeGroup();
                    m_ListBox.append(comp);
                    Increment(); // Progressbar
                    WatchListComponent::_().CheckWatchList(m_Name, comp);
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