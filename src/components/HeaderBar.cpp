//
// Created by htrap19 on 4/4/22.
//

#include "HeaderBar.h"
#include "RootContent.h"
#include "utils/TaskQueue.h"

namespace PC
{
    HeaderBar::HeaderBar(Gtk::Widget& key_capture_widget)
        : m_SearchButton("_Search", true)
    {
        m_SearchButton.signal_clicked().connect(sigc::mem_fun(*this, &HeaderBar::handle_search));
        m_SearchEntry.property_activates_default().set_value(true);
        m_SearchEntry.set_key_capture_widget(key_capture_widget);

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
            TaskQueue::_().Push(&RootContent::Search, &RootContent::_(), search_text);
    }
}