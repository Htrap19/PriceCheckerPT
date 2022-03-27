//
// Created by Htrap19 on 3/22/2022.
//

#include "ContinenteContent.h"
#include <Node.h>
#include <iostream>
#include <cstring>

namespace ps
{
    ContinenteContent::ContinenteContent()
    {
//        m_Products.emplace_back("Something more and more", "45.00", "assets/imac.png");
//        m_Products.emplace_back("Else", "45.00", "assets/imac.png");
//        m_Products.emplace_back("Yo yo", "45.00", "assets/imac.png");
//        m_Products.emplace_back("Working", "45.00", "assets/imac.png");
//        m_Products.emplace_back("Testing", "45.00", "assets/imac.png");
//        m_Products.emplace_back("What is the for", "45.00", "assets/imac.png");
//
//        for (auto& productComp : m_Products)
//            m_FlowBox.append(productComp);

        m_FlowBox.set_homogeneous(true);
        m_FlowBox.set_valign(Gtk::Align::START);
        set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        set_child(m_FlowBox);
    }

    void ContinenteContent::Search(const std::string& search_text)
    {
        std::stringstream productNameStr(search_text);
        std::string token;
        std::string productNameUrlFormat;
        while (std::getline(productNameStr, token, ' '))
            productNameUrlFormat += token + "+";
        productNameUrlFormat = productNameUrlFormat.substr(0, productNameUrlFormat.size() - 1);
        auto url = std::string("https://www.continente.pt/pesquisa/?q=") + productNameUrlFormat + "&start=0";
        std::cout << url << std::endl;
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
            m_Products.emplace_back(productName, formattedPrice, "assets/imac.png");
        }

        for (auto& productCom : m_Products)
            m_FlowBox.append(productCom);
    }

    void ContinenteContent::FetchErrCallback(const std::string& what)
    {
        std::cout << "Error from Continente: " << what << std::endl;
    }
}
