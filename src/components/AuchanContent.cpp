//
// Created by Htrap19 on 3/22/2022.
//

#include "AuchanContent.h"

namespace ps
{
    AuchanContent::AuchanContent()
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

    void AuchanContent::Search(const std::string& search_text)
    {
        std::cout << search_text << std::endl;
    }

    void AuchanContent::FetchCallback(CDocument& doc)
    {

    }

    void AuchanContent::FetchErrCallback(const std::string &what)
    {
        std::cout << "Error from Auchan: " << what << std::endl;
    }
}