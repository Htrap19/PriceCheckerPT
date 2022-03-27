//
// Created by Htrap19 on 3/22/2022.
//

#include "RootVBox.h"
#include "InfoBar.h"

namespace ps
{
    RootVBox::RootVBox()
        : m_MainVBox(Gtk::Orientation::VERTICAL, 10),
        m_SearchHBox(Gtk::Orientation::HORIZONTAL, 10),
        m_SearchButton("Search")
    {
        m_SearchHBox.set_halign(Gtk::Align::CENTER);
        m_SearchHBox.prepend(m_SearchEntry);
        m_SearchHBox.append(m_SearchButton);

        m_SearchButton.signal_clicked().connect(sigc::mem_fun(*this, &RootVBox::handle_search));

        m_SearchEntry.signal_stop_search().connect(sigc::mem_fun(*this, &RootVBox::search_stop));
        m_SearchBar.set_search_mode(true);
        m_SearchBar.set_child(m_SearchHBox);
        m_SearchEntry.set_enable_undo(true);

        m_MainVBox.prepend(m_SearchBar);
        m_MainVBox.append(m_Content);
        m_Content.set_expand();

        set_child(m_MainVBox);
        add_overlay(InfoBar::_());
    }

    void RootVBox::search_stop()
    {
        m_SearchBar.set_search_mode(true);
    }

    void RootVBox::handle_search()
    {
        auto search_text = m_SearchEntry.get_text();
        if (!search_text.empty())
            m_Content.Search(m_SearchEntry.get_text());
    }
}