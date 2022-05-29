//
// Created by htrap19 on 5/9/22.
//

#include "SparContent.h"
#include "utils/UIQueue.h"
#include <Node.h>

namespace PC
{
    SparContent::SparContent()
        : SearchableContent("Spar", "www.spar.pt")
    {
    }

    void SparContent::Search(const std::string& search_text)
    {
        auto productNameUrlFormat = ConvertToUrlQuery(search_text);
        auto url = "https://www.spar.pt/search?q=" + productNameUrlFormat + "&pagesize=12";

        SearchableContent::Search(url);
    }

    void SparContent::ParseSearchableContent(CDocument& doc)
    {
        auto selection = doc.find("div.product-item");
        SetTotalItemsCount(selection.nodeNum());
        for (size_t i = 0; (i < selection.nodeNum() && IsRunning()); i++)
        {
            try
            {
                auto node = selection.nodeAt(i);
                if (!node.valid() || node.childNum() == 0)
                    continue;

                auto imgNodeSelection = node.find("div.picture");
                if (imgNodeSelection.nodeNum() == 0 || imgNodeSelection.nodeAt(0).childNum() == 0)
                    continue;
                auto imgNode = imgNodeSelection.nodeAt(0).childAt(0);
                auto productName = imgNode.attribute("title");
                auto productImageSrc = imgNode.childAt(1).attribute("src");

                auto detailsNode = node.find("div.details");
                auto actualPriceNodeSelection = detailsNode.find("span.actual-price");
                if (actualPriceNodeSelection.nodeNum() == 0)
                    continue;
                std::string actualPrice = actualPriceNodeSelection.nodeAt(0).text();

                std::string oldPrice;
                auto oldPriceNode = detailsNode.find("span.old-price");
                if (oldPriceNode.nodeNum() > 0)
                    oldPrice = oldPriceNode.nodeAt(0).text();

                std::string secondaryPrice;
                auto secondaryPriceNode = detailsNode.find("div.base-price-pangv");
                if (secondaryPriceNode.nodeNum() > 0)
                    secondaryPrice = secondaryPriceNode.nodeAt(0).text();

                auto& comp = m_Products.emplace_back(
                         productName,
                         "", "",
                         oldPrice,
                         actualPrice,
                         secondaryPrice,
                         productImageSrc);
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