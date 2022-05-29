//
// Created by htrap19 on 4/3/22.
//

#include "CssProvider.h"
#include "utils/AssetManager.h"
#include <mutex>

namespace PC
{
    static Glib::RefPtr<Gtk::CssProvider> s_CssProvider = Gtk::CssProvider::create();
    static std::once_flag s_CssLoadedFlag;

    void CssProvider::LoadProvider(Gtk::Widget& widget)
    {
        std::call_once(s_CssLoadedFlag, []() { s_CssProvider->load_from_data(ASSET(Mics, "styles")); });

        widget.get_style_context()->add_provider(s_CssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    }
}