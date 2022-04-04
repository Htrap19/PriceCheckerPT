//
// Created by htrap19 on 4/3/22.
//

#include "CssProvider.h"

namespace PC
{
    Glib::RefPtr<Gtk::CssProvider> CssProvider::s_CssProvider = Gtk::CssProvider::create();
    bool CssProvider::s_LoadCssFile = true;
    static const std::string s_CssFilePath = "assets/styles/styles.css";

    void CssProvider::LoadProvider(Gtk::Widget& widget)
    {
        if (s_LoadCssFile)
        {
            s_CssProvider->load_from_path(s_CssFilePath);
            s_LoadCssFile = false;
        }

        widget.get_style_context()->add_provider(s_CssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
}