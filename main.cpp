#include <gtkmm.h>

#include "src/components/Window.h"
#include "src/components/InfoBar.h"

#if defined(PC_PLATFORM_WINDOWS) && defined(PC_RELEASE)
#include <windows.h>
#endif

Glib::RefPtr<Gtk::Application> app;

int main(int argc, char* argv[])
{
#if defined(PC_PLATFORM_WINDOWS) && defined(PC_RELEASE)
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif
    try
    {
        app = Gtk::Application::create("price.checker");
        return app->make_window_and_run<PC::Window>(argc, argv);
    }
    catch (std::exception& e)
    { PC::INFO_BAR(Error, e.what()); }
}
