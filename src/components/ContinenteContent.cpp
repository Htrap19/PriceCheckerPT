//
// Created by Htrap19 on 3/22/2022.
//

#include "ContinenteContent.h"
#include <iostream>
#include <cstring>

namespace ps
{
    ContinenteContent::ContinenteContent()
    {
        m_Products.emplace_back("Something more and more", "45.00", "assets/imac.png");
        m_Products.emplace_back("Else", "45.00", "assets/imac.png");
        m_Products.emplace_back("Yo yo", "45.00", "assets/imac.png");
        m_Products.emplace_back("Working", "45.00", "assets/imac.png");
        m_Products.emplace_back("Testing", "45.00", "assets/imac.png");
        m_Products.emplace_back("What is the for", "45.00", "assets/imac.png");

        for (auto& productComp : m_Products)
            m_FlowBox.append(productComp);

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
        auto url = std::string("https://www.continente.pt/pesquisa/?q=") + productNameUrlFormat;
        std::cout << url << std::endl;
        Fetch(url);
    }

    static void GetChildContent(GumboNode* node)
    {
        if (node->type != GUMBO_NODE_ELEMENT)
            return;

        auto element = node->v.element;
        if (element.tag == GUMBO_TAG_IMG)
        {
            auto* imgClassName = gumbo_get_attribute(&element.attributes, "class");
            if (imgClassName && (std::strcmp(imgClassName->value, "ct-tile-image lazyloaded hidden") == 0))
            {
                auto* productName = gumbo_get_attribute(&element.attributes, "title");
                auto* imgSrc = gumbo_get_attribute(&element.attributes, "src");
                if (productName && imgSrc)
                    std::cout << "\nProduct Name: " << productName->value << "\n Product Src: " << imgSrc->value << std::endl;
            }
        }

        auto* children = &node->v.element.children;
        for (uint32_t i = 0; i < children->length; i++)
            GetChildContent(static_cast<GumboNode*>(children->data[i]));
    }

    void ContinenteContent::FetchCallback(GumboNode* root)
    {
        if (root->type != GUMBO_NODE_ELEMENT)
            return;

        if (root->v.element.tag == GUMBO_TAG_DIV)
        {
            GumboAttribute* className = gumbo_get_attribute(&root->v.element.attributes, "class");
            if (className && (std::strcmp(className->value, "product") == 0))
                GetChildContent(root);
        }

        auto* children = &root->v.element.children;
        for (uint32_t i = 0; i < children->length; i++)
            FetchCallback(static_cast<GumboNode*>(children->data[i]));
    }

    void ContinenteContent::FetchErrCallback(const std::string& what)
    {
        std::cout << "Error from Continente: " << what << std::endl;
    }
}
