//
// Created by Htrap19 on 3/22/2022.
//

#include "ContinenteContent.h"
#include "utils/UIQueue.h"
#include <Node.h>

namespace PC
{
    ContinenteContent::ContinenteContent()
        : SearchableContent("Continente", "www.continente.pt")
    {
    }

    void ContinenteContent::Search(const std::string& search_text)
    {
        auto productNameUrlFormat = ConvertToUrlQuery(search_text);
        auto url = std::string("https://www.continente.pt/pesquisa/?q=") + productNameUrlFormat + "&start=0";

        SearchableContent::Search(url);
    }

    void ContinenteContent::ParseSearchableContent(CDocument& doc)
    {
        auto selection = doc.find("div.product");
        SetTotalItemsCount(selection.nodeNum());
        for (size_t i = 0; (i < selection.nodeNum() && IsRunning()); i++)
        {
            try
            {
                auto node = selection.nodeAt(i);
                if (!node.valid() || node.childNum() == 0)
                    continue;

                auto imgNodeSelection = node.find("img.ct-tile-image");
                if (imgNodeSelection.nodeNum() == 0)
                    continue;
                auto imgNode = imgNodeSelection.nodeAt(0);

                // Product Name
                auto productName = imgNode.attribute("title");

                // Product Img
                auto productImgSrc = imgNode.attribute("data-src");

                // Product Prices
                auto priceNodeSelection = node.find("span.value");
                if (priceNodeSelection.nodeNum() == 0 || priceNodeSelection.nodeAt(0).childNum() == 0)
                    continue;

                auto priceNode = priceNodeSelection.nodeAt(0);
                auto actualFormattedPrice = priceNode.childAt(1).text() + priceNode.childAt(3).text();
                Utils::RemoveEmptySpace(actualFormattedPrice);

                auto originalPriceNode = node.find("span.ct-tile--price-value");
                std::string originalPrice;
                if (originalPriceNode.nodeNum() > 0)
                {
                    auto originalPriceNodeValue = originalPriceNode.nodeAt(0);
                    originalPrice = originalPriceNodeValue.childAt(2).text() + originalPriceNodeValue.childAt(3).text();
                    Utils::RemoveEmptySpace(originalPrice);
                }

                auto secondaryPriceDescNode = node.find("div.ct-tile--price-secondary");
                std::string secondaryPriceDesc;
                if (secondaryPriceDescNode.nodeNum() > 0)
                    secondaryPriceDesc = secondaryPriceDescNode.nodeAt(0).childAt(1).text() + secondaryPriceDescNode.nodeAt(0).childAt(3).text();
                Utils::RemoveEmptySpace(secondaryPriceDesc);

                // Product Branding
                auto productBrand = node.find("p.ct-tile--brand").nodeAt(0).text();

                // Product Packaging
                auto productPackaging = node.find("p.ct-tile--quantity").nodeAt(0).text();

                auto& comp = m_Products.emplace_back(
                            productName,
                            productBrand,
                            productPackaging,
                            originalPrice,
                            actualFormattedPrice,
                            secondaryPriceDesc,
                            productImgSrc,
                            true);

                UI([&]()
                {
                    comp.AddToSizeGroup();
                    m_ListBox.append(comp);
                    Increment(); // Progressbar
                });
            }
            catch(std::exception& e)
            {
#ifdef PC_DEBUG
                std::cout << e.what() << std::endl;
#endif
                SearchableContent::FetchErrCallback(e.what());
            }
        }
    }
}
