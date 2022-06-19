//
// Created by htrap19 on 3/27/22.
//

#ifndef PRICECHECKER_INFOBAR_H
#define PRICECHECKER_INFOBAR_H

#include <gtkmm.h>
#include "utils/Utils.h"
#include "utils/AssetManager.h"

namespace PC
{
    class InfoBar : public Gtk::InfoBar // SingleTon
    {
    public:
        SINGLE_TON(InfoBar)

        inline void Info(const std::string& info_text) { m_Icon.set(ASSET(Image, "info")); SetText(Gtk::MessageType::INFO, info_text); }
#ifdef PC_PLATFORM_WINDOWS
        inline void Error(const std::string& error_text) { m_Icon.set(ASSET(Image, "error")); SetText(Gtk::MessageType::INFO, error_text); } // TODO: Check this issue for MessageType::Error enum on msys2(Windows)
#else
        inline void Error(const std::string& error_text) { m_Icon.set(ASSET(Image, "error")); SetText(Gtk::MessageType::ERROR, error_text); }
#endif
        inline void Warn(const std::string& warning_text) { m_Icon.set(ASSET(Image, "warning")); SetText(Gtk::MessageType::WARNING, warning_text); }
        inline void Question(const std::string& question_text) { m_Icon.set(ASSET(Image, "question")); SetText(Gtk::MessageType::QUESTION, question_text); }
        inline void Text(const std::string& text) { m_Icon.set(ASSET(Image, "paragraph")); SetText(Gtk::MessageType::OTHER, text); }

        template <typename Callable, typename ... Args>
        void Ask(const std::string& question, Callable&& func, Args&& ... args)
        {
            m_Yes.show();
            m_No.show();
            Question(question);
            set_show_close_button(false);
            m_ConfirmCallback = std::bind(func, std::forward<Args>(args)...);
        }

    private:
        InfoBar();
        void SetText(Gtk::MessageType messageType, const std::string& text);
        void handle_on_response(int response_id);

    private:
        Gtk::Label m_Message;
        Gtk::Image m_Icon;
        Gtk::Button m_Yes, m_No;
        std::function<void()> m_ConfirmCallback;
    };
}

#define INFO_BAR(func, ...) InfoBar::_().func(__VA_ARGS__)

#endif //PRICECHECKER_INFOBAR_H
