#include <gtkmm.h>

#include "src/components/Window.h"

#ifdef PC_PLATFORM_WINDOWS
#include <windows.h>
#endif

Glib::RefPtr<Gtk::Application> app;

int main(int argc, char* argv[])
{
#ifdef PC_PLATFORM_WINDOWS
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif

    app = Gtk::Application::create("price.checker");
    return app->make_window_and_run<PC::Window>(argc, argv);
}
