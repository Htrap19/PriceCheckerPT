//
// Created by Htrap19 on 3/22/2022.
//

#include "ContentVBox.h"
#include "ContinenteContent.h"
#include "AuchanContent.h"

namespace ps
{
    ContentVBox::ContentVBox()
        : Gtk::Box(Gtk::Orientation::VERTICAL, 10),
        m_Paned(Gtk::Orientation::HORIZONTAL)
    {
        m_SearchableList.emplace_back(std::make_shared<ContinenteContent>());
        m_SearchableList.emplace_back(std::make_shared<AuchanContent>());

        m_Paned.set_start_child(m_SearchableList[0]->GetWidget());
        m_Paned.set_end_child(m_SearchableList[1]->GetWidget());

        prepend(m_Paned);
        m_Paned.set_expand(true);
    }

    void ContentVBox::Search(const std::string& search_text)
    {
        for (auto& searchEntity : m_SearchableList)
            searchEntity->Search(search_text);
    }
}