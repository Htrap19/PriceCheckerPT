//
// Created by htrap19 on 4/4/22.
//

#include "HeaderBar.h"
#include "RootContent.h"
#include <thread>

namespace PC
{
    HeaderBar::HeaderBar()
        : m_SearchButton("_Search", true)
    {
        m_SearchButton.signal_clicked().connect(sigc::mem_fun(*this, &HeaderBar::handle_search));

        set_title_widget(m_TitleLabel);
        set_show_title_buttons(true);
        pack_start(m_SearchEntry);
        pack_start(m_SearchButton);
        pack_end(m_Spinner);
    }

    void HeaderBar::handle_search()
    {
        auto search_text = m_SearchEntry.get_text();
        if (!search_text.empty())
        {
            std::thread search_thread(&RootContent::Search, &RootContent::_(), search_text);
            search_thread.detach();
        }
    }
}