//
// Created by Htrap19 on 3/22/2022.
//

#include "AuchanContent.h"
#include "components/InfoBar.h"
#include "Node.h"
#include "utils/Utils.h"
#include "utils/LanguageManager.h"

namespace PC
{
    AuchanContent::AuchanContent()
        : SearchableContent("Auchan", "www.auchan.pt")
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
        for (size_t i = 0; i < selection.nodeNum(); i++)
        {
            try
            {
                auto node = selection.nodeAt(i);
                auto imgNode = node.find("img.tile-image").nodeAt(0);

                // Product Name
                auto productName = imgNode.attribute("title");

                // Product Image
                auto productImgSrc = imgNode.attribute("data-src");

                // Product Price
                auto priceNode = node.find("span.sales").nodeAt(0);
                auto price = priceNode.childAt(1).text();
                Utils::RemoveEmptySpace(price);

                auto originalPriceNode = node.find("span.strike-through");
                std::string originalPrice = "-";
                if (originalPriceNode.nodeNum() > 0)
                    originalPrice = originalPriceNode.nodeAt(0).childAt(2).text();
                Utils::RemoveEmptySpace(originalPrice);

                auto secondaryPriceDescNode = node.find("div.auc-measures");
                auto secondaryPriceDesc = secondaryPriceDescNode.nodeAt(0).text();
                Utils::RemoveEmptySpace(secondaryPriceDesc);

                PushProduct({
                            productName,
                "", "",
                            originalPrice,
                            price,
                            secondaryPriceDesc,
                            productImgSrc});
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