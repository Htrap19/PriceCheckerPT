#include <gtkmm.h>

#include "src/components/Window.h"

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("price.checker");
    return app->make_window_and_run<ps::Window>(argc, argv);
}
