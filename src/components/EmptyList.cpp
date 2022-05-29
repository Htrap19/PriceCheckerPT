//
// Created by htrap19 on 4/4/22.
//

#include "EmptyList.h"
#include "utils/AssetManager.h"

namespace PC
{
    EmptyList::EmptyList(const std::string& nothing_label)
        : Gtk::Box(Gtk::Orientation::VERTICAL, 10),
        m_Nothing(nothing_label),
        m_OpenBoxImage(ASSET(Image, "open_box"))
    {
        set_valign(Gtk::Align::CENTER);
        set_halign(Gtk::Align::CENTER);
        set_opacity(0.4);
        m_OpenBoxImage.set_pixel_size(128);

        prepend(m_OpenBoxImage);
        append(m_Nothing);
    }
}