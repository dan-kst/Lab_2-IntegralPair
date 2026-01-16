#include "database/IStorage.hpp"
#include "gui/MainWindow.hpp"
#include <gtkmm/application.h>

int
main (int argc, char *argv[])
{
  auto app = Gtk::Application::create ("org.gtkmm.lab3");

  return app->make_window_and_run<Gui::MainWindow> (
      argc, argv, Core::createStorage ("lab3.db"));
}
