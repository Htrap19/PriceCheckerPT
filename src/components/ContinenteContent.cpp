//
// Created by Htrap19 on 3/22/2022.
//

#include "ContinenteContent.h"
#include "InfoBar.h"
#include <Node.h>
#include <cstring>

namespace PC
{
    ContinenteContent::ContinenteContent()
    {
        m_FlowBox.set_homogeneous(true);
        m_FlowBox.set_valign(Gtk::Align::START);
        set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        set_child(m_FlowBox);
    }

    void ContinenteContent::Search(const std::string& search_text)
    {
        auto productNameUrlFormat = ConvertToUrlQuery(search_text);
        auto url = std::string("https://www.continente.pt/pesquisa/?q=") + productNameUrlFormat + "&start=0";

        InfoBar::_().Info("Fetching result from www.continente.pt!");
        Fetch(url);
    }

    void ContinenteContent::FetchCallback(CDocument& doc)
    {
        for (auto& productCom : m_Products)
            m_FlowBox.remove(productCom);
        m_Products.clear();

        auto selection = doc.find("div.product");
        for (size_t i = 0; i < selection.nodeNum(); i++)
        {
            auto node = selection.nodeAt(i).find("img.ct-tile-image");
            auto imgNode = node.nodeAt(0);
            auto productName = imgNode.attribute("title");
            auto productImgSrc = imgNode.attribute("data-src");

            auto priceNode = selection.nodeAt(i).find("span.sales span.value").nodeAt(0);
            auto formattedPrice = priceNode.childAt(0).text() + priceNode.childAt(1).text();
            formattedPrice.erase(std::remove_if(formattedPrice.begin(),
                                                formattedPrice.end(),
                                                [](unsigned char x) { return std::isspace(x); }), formattedPrice.end());
            auto& productCom = m_Products.emplace_back(productName, formattedPrice, productImgSrc);
            m_FlowBox.append(productCom);
        }
    }

    void ContinenteContent::FetchErrCallback(const std::string& what)
    {
        InfoBar::_().Error(what);
    }
}
