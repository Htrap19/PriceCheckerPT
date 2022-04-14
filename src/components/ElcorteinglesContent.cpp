//
// Created by htrap19 on 4/14/22.
//

#include "ElcorteinglesContent.h"
#include "InfoBar.h"
#include "utils/Utils.h"
#include <Node.h>

namespace PC
{

    ElcorteinglesContent::ElcorteinglesContent()
        : SearchableContent("Elcorteingles")
    {
    }

    void ElcorteinglesContent::Search(const std::string& search_text)
    {
        auto productNameUrlFormat = ConvertToUrlQuery(search_text);
        auto url = std::string("https://www.elcorteingles.pt/supermercado/pesquisar/?term=") + productNameUrlFormat + "&search=text";
        InfoBar::_().Info("Fetching result from www.elcorteingles.pt!");
        Fetch(url);
    }

    void ElcorteinglesContent::FetchCallback(CDocument& doc)
    {
        ClearProductList();

        auto selection = doc.find("div.product_tile");
        for (size_t i = 0; i < selection.nodeNum(); i++)
        {
            try
            {
                auto node = selection.nodeAt(i);
                auto imgNode = node.find("a.js-product-link").nodeAt(0).childAt(0);

                // Product Name
                auto productName = imgNode.attribute("title");

                // Product Image
                auto productImgSrc = "https:" + imgNode.attribute("src");

                // Product Prices
                auto priceNode = node.find("div.product_tile-prices").nodeAt(0).childAt(0);
                std::string actualPrice, originalPrice, secondaryPriceDesc;
                if (priceNode.childNum() >= 2 && priceNode.childNum() < 6)
                {
                    actualPrice = priceNode.childAt(0).text();
                    secondaryPriceDesc = priceNode.childAt(1).text();
                }
                else
                {
                    originalPrice = priceNode.childAt(0).text();
                    actualPrice = priceNode.childAt(2).text();
                    secondaryPriceDesc = priceNode.childAt(3).text();
                }
                Utils::RemoveEmptySpace(originalPrice);
                Utils::RemoveEmptySpace(actualPrice);
                Utils::RemoveEmptySpace(secondaryPriceDesc);

                auto& comp = m_Products.emplace_back(productName,
                                        "",
                                        "",
                                        originalPrice,
                                        actualPrice,
                                        secondaryPriceDesc,
                                        productImgSrc,
                                        false);
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

        SearchableContent::FetchCallback(doc);
    }
}