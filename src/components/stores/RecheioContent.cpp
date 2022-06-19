//
// Created by htrap19 on 6/19/22.
//

#include "RecheioContent.h"
#include "utils/UIQueue.h"
#include "utils/ConfigManager.h"
#include <Node.h>

namespace PC
{
    RecheioContent::RecheioContent()
        : SearchableContent("Recheio", true)
    {
    }

    void RecheioContent::Search(const std::string& search_text)
    {
        auto productNameUrlFormat = ConvertToUrlQuery(search_text);
        auto postfixUrl = CONFIG(GetLang) == "en" ? "/en/store" : "/catalogo";
        auto url = std::string("https://www.recheio.pt") + postfixUrl + "/catalogsearch/result/?q=" + productNameUrlFormat + "&order=relevance&dir=desc&cat=745";

        SearchableContent::Search(url);
    }

    void RecheioContent::ParseSearchableContent(CDocument& doc)
    {
        auto selection = doc.find("li.item");
        SetTotalItemsCount(selection.nodeNum());
        for (size_t i = 0; (i < selection.nodeNum() && IsRunning()); i++)
        {
            try
            {
                auto node = selection.nodeAt(i);
                if (!node.valid() || node.childNum() == 0)
                    continue;

                auto imgNodeSelection = node.find("a.product-image");
                if (imgNodeSelection.nodeNum() == 0 || imgNodeSelection.nodeAt(0).childNum() == 0)
                    continue;

                auto imgNode = imgNodeSelection.nodeAt(0);

                // Product Name
                auto productName = imgNode.attribute("title");

                // Product Image
                auto productImgSrc = imgNode.childAt(1).attribute("src");

                // Product Price
                auto productPriceSelection = node.find("span.price-excluding-tax");
                std::string price = "-";
                if (productPriceSelection.nodeNum() > 0)
                    price = productPriceSelection.nodeAt(0).text();
                Utils::RemoveEmptySpace(price);

                // Product Price Description
                auto productPriceDescSelection = node.find("span.price-including-tax");
                std::string priceDesc;
                if (productPriceDescSelection.nodeNum() > 0)
                {
                    for (size_t j = 0; j < productPriceDescSelection.nodeNum(); j++)
                    {
                        auto value = productPriceDescSelection.nodeAt(j).text();
                        Utils::RemoveEmptySpace(value);
                        priceDesc += value + " | ";
                    }
                }
                priceDesc = priceDesc.substr(0, priceDesc.find_last_of('|'));

                auto& comp = m_Products.emplace_back(
                        productName,
                        "", "",
                        "",
                        price,
                        priceDesc,
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