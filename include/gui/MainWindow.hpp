#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "core/Pair.hpp"
#include "database/IStorage.hpp"
#include <gtkmm.h>
#include <memory>
#include <vector>

namespace Gui
{

class MainWindow : public Gtk::Window
{
public:
  MainWindow (std::unique_ptr<Core::IStorage> storage);
  ~MainWindow () override = default;

protected:
  // Signal Handlers
  void on_button_add_clicked ();
  void on_button_adjust_selected (int val);
  void on_button_delete_selected ();
  void on_selection_changed ();

  // Storage and Logic
  std::unique_ptr<Core::IStorage> storage_;
  std::vector<std::unique_ptr<Core::Pair> > dataStorage_;

  void refresh_list ();
  std::vector<int> get_selected_indices ();

  // GTK 4 Layout Components
  Gtk::Box m_MainBox{ Gtk::Orientation::VERTICAL, 15 };
  Gtk::Paned m_Paned{ Gtk::Orientation::HORIZONTAL };

  // TreeView
  struct ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
    Gtk::TreeModelColumn<int> col_id;
    Gtk::TreeModelColumn<Glib::ustring> col_type;
    Gtk::TreeModelColumn<Glib::ustring> col_display;
    ModelColumns ()
    {
      add (col_id);
      add (col_type);
      add (col_display);
    }
  };

  ModelColumns m_Columns;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

  // Interaction Controls
  Gtk::Box m_ControlBox{ Gtk::Orientation::VERTICAL, 10 };

  // Creation Section
  Gtk::Label m_LabelCreate;
  Gtk::DropDown m_DropDownType;
  Glib::RefPtr<Gtk::StringList> m_TypeOptions;
  Gtk::Entry m_EntryFirst;
  Gtk::Entry m_EntrySecond;
  Gtk::Button m_ButtonAdd{ "Add to List" };

  // Selection Section
  Gtk::Label m_LabelSelection;
  Gtk::Button m_ButtonIncSelected{ "Adjust Selected (+10)" };
  Gtk::Button m_ButtonDecSelected{ "Adjust Selected (-10)" };
  Gtk::Button m_ButtonDelete{ "Delete Selected" };
};

} // namespace Gui

#endif
