//
// Created by htrap19 on 5/9/22.
//

#include "SparContent.h"
#include "components/InfoBar.h"
#include "utils/LanguageManager.h"
#include <Node.h>

namespace PC
{
    SparContent::SparContent()
        : SearchableContent("Spar")
    {
    }

    void SparContent::Search(const std::string& search_text)
    {
        auto productNameUrlFormat = ConvertToUrlQuery(search_text);
        auto url = "https://www.spar.pt/search?q=" + productNameUrlFormat + "&pagesize=12";

        INFO_BAR(Info, LANGUAGE(fetching_result_from) + " www.spar.pt!");
        Fetch(url);
    }

    void SparContent::ParseSearchableContent(CDocument& doc)
    {
        auto selection = doc.find("div.product-item");

        for (size_t i = 0; i < selection.nodeNum(); i++)
        {
            try
            {
                auto node = selection.nodeAt(i);

                auto imgNode = node.find("div.picture").nodeAt(0).childAt(0);
                auto productName = imgNode.attribute("title");
                auto productImageSrc = imgNode.childAt(1).attribute("src");

                auto detailsNode = node.find("div.details");
                std::string actualPrice = detailsNode.find("span.actual-price").nodeAt(0).text();

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
                m_ListBox.append(comp);
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