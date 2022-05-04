//
// Created by htrap19 on 3/27/22.
//

#include "InfoBar.h"

namespace PC
{
    static Glib::RefPtr<Gtk::SizeGroup> s_ButtonSizeGroup = Gtk::SizeGroup::create(Gtk::SizeGroup::Mode::BOTH);

    InfoBar::InfoBar()
        : m_Yes("_Yes", true),
        m_No("_No", true)
    {
        set_valign(Gtk::Align::END);
        set_halign(Gtk::Align::FILL);

        signal_response().connect(sigc::mem_fun(*this, &InfoBar::handle_on_response));

        add_child(m_Message);
        set_show_close_button();
        set_revealed(false);
        add_action_widget(m_Yes, Gtk::ResponseType::YES);
        add_action_widget(m_No, Gtk::ResponseType::NO);
        m_Yes.set_margin_end(5);
        m_No.set_margin_start(5);
        m_Yes.hide();
        m_No.hide();

        s_ButtonSizeGroup->add_widget(m_Yes);
        s_ButtonSizeGroup->add_widget(m_No);
    }

    void InfoBar::SetText(Gtk::MessageType messageType, const std::string& text)
    {
        set_message_type(messageType);
        m_Message.set_text(text);

        if (!get_revealed())
            set_revealed();

        if (!get_show_close_button())
            set_show_close_button();
    }

    void InfoBar::handle_on_response(int response_id)
    {
        if (response_id == Gtk::ResponseType::YES)
        {
            m_ConfirmCallback();
            m_ConfirmCallback = []() {};
        }

        m_Message.set_text("");
        set_revealed(false);
    }
}