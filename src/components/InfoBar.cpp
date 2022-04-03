//
// Created by htrap19 on 3/27/22.
//

#include "InfoBar.h"

namespace PC
{
    InfoBar::InfoBar()
    {
        set_valign(Gtk::Align::END);
        set_halign(Gtk::Align::FILL);

        signal_response().connect(sigc::mem_fun(*this, &InfoBar::handle_on_response));

        add_child(m_Message);
        set_show_close_button();
        set_revealed(false);
    }

    void InfoBar::SetText(Gtk::MessageType messageType, const std::string& text)
    {
        set_message_type(messageType);
        m_Message.set_text(text);

        if (!get_revealed())
            set_revealed();
    }

    void InfoBar::handle_on_response(int response_id)
    {
        m_Message.set_text("");
        set_revealed(false);
    }
}