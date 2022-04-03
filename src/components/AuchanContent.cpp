//
// Created by Htrap19 on 3/22/2022.
//

#include "AuchanContent.h"
#include "InfoBar.h"
#include "Node.h"

namespace PC
{
    AuchanContent::AuchanContent()
    {
        m_FlowBox.set_homogeneous(true);
        m_FlowBox.set_valign(Gtk::Align::START);
        set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        set_child(m_FlowBox);
    }

    void AuchanContent::Search(const std::string& search_text)
    {
        auto productNameUrlFormat = ConvertToUrlQuery(search_text);
        auto url = std::string("https://www.auchan.pt/pt/pesquisa?q=") + productNameUrlFormat + "&search-button=&lang=pt_PT";

        InfoBar::_().Info("Fetching result from www.auchan.pt!");
        Fetch(url);
    }

    void AuchanContent::FetchCallback(CDocument& doc)
    {
        for (auto& productCom : m_Products)
            m_FlowBox.remove(productCom);
        m_Products.clear();

        auto selection = doc.find("div.auc-product");
        for (size_t i = 0; i < selection.nodeNum(); i++)
        {
            auto node = selection.nodeAt(i).find("img.tile-image");
            auto imgNode = node.nodeAt(0);
            auto productName = imgNode.attribute("title");
            auto productImgSrc = imgNode.attribute("data-src");

            auto priceNode = selection.nodeAt(i).find("span.sales").nodeAt(0);
            auto price = priceNode.childAt(1).text();
            price.erase(std::remove_if(price.begin(),
                                       price.end(),
                                       [](unsigned char x) { return std::isspace(x); }), price.end());
            auto& productCom = m_Products.emplace_back(productName, price, productImgSrc);
            m_FlowBox.append(productCom);
        }
    }

    void AuchanContent::FetchErrCallback(const std::string& what)
    {
        InfoBar::_().Error(what);
    }
}