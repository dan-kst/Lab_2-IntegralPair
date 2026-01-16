#include "gui/MainWindow.hpp"
#include "core/Factory.hpp"
#include <algorithm>
#include <string>

namespace Gui
{

MainWindow::MainWindow (std::unique_ptr<Core::IStorage> storage)
    : storage_ (std::move (storage))
{

  set_title ("Lab 3 - GTKmm 4 Multi-Select Manager");
  set_default_size (950, 550);

  // 1. Data Initialization
  dataStorage_ = storage_->loadAll ();

  // 2. TreeView Setup
  m_refTreeModel = Gtk::ListStore::create (m_Columns);
  m_TreeView.set_model (m_refTreeModel);
  m_TreeView.append_column ("ID", m_Columns.col_id);
  m_TreeView.append_column ("Type", m_Columns.col_type);
  m_TreeView.append_column ("Display Value", m_Columns.col_display);
  m_TreeView.set_expand (true);

  m_TreeView.get_selection ()->set_mode (Gtk::SelectionMode::MULTIPLE);

  m_ScrolledWindow.set_child (m_TreeView);
  m_ScrolledWindow.set_policy (Gtk::PolicyType::AUTOMATIC,
                               Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand (true);

  // 3. Control Panel Setup
  m_ControlBox.set_margin (15);
  m_ControlBox.set_size_request (100);

  // --- Creation Section ---
  m_LabelCreate.set_markup ("<b>Create New Pair</b>");
  m_TypeOptions
      = Gtk::StringList::create ({ "Angle (Degrees)", "Angle (Radians)" });
  m_DropDownType.set_model (m_TypeOptions);
  m_DropDownType.set_selected (0);
  m_EntryFirst.set_placeholder_text ("First (Deg/Int)");
  m_EntrySecond.set_placeholder_text ("Second (Min/Frac)");

  m_ControlBox.append (m_LabelCreate);
  m_ControlBox.append (m_DropDownType);
  m_ControlBox.append (m_EntryFirst);
  m_ControlBox.append (m_EntrySecond);
  m_ControlBox.append (m_ButtonAdd);

  m_ControlBox.append (
      *Gtk::make_managed<Gtk::Separator> (Gtk::Orientation::HORIZONTAL));

  // --- Selection Section (Bulk Actions) ---
  m_LabelSelection.set_markup ("<b>Bulk Actions</b>");
  m_ControlBox.append (m_LabelSelection);
  m_ControlBox.append (m_ButtonIncSelected);
  m_ControlBox.append (m_ButtonDecSelected);
  m_ControlBox.append (m_ButtonDelete);

  // 4. Layout
  m_Paned.set_start_child (m_ScrolledWindow);
  m_Paned.set_end_child (m_ControlBox);
  m_Paned.set_position (650);
  set_child (m_Paned);
  set_size_request (250, 250);

  // 5. Connect Signals
  m_ButtonAdd.signal_clicked ().connect (
      sigc::mem_fun (*this, &MainWindow::on_button_add_clicked));
  m_ButtonIncSelected.signal_clicked ().connect (sigc::bind (
      sigc::mem_fun (*this, &MainWindow::on_button_adjust_selected), 10));
  m_ButtonDecSelected.signal_clicked ().connect (sigc::bind (
      sigc::mem_fun (*this, &MainWindow::on_button_adjust_selected), -10));
  m_ButtonDelete.signal_clicked ().connect (
      sigc::mem_fun (*this, &MainWindow::on_button_delete_selected));

  m_TreeView.get_selection ()->signal_changed ().connect (
      sigc::mem_fun (*this, &MainWindow::on_selection_changed));

  on_selection_changed ();
  refresh_list ();
}

void
MainWindow::refresh_list ()
{
  m_refTreeModel->clear ();
  int id = 0;
  for (const auto &obj : dataStorage_)
    {
      auto row = *(m_refTreeModel->append ());
      row[m_Columns.col_id] = id++;
      row[m_Columns.col_type]
          = (obj->getType () == Core::PairType::Degrees ? "Degrees"
                                                        : "Radians");
      row[m_Columns.col_display] = obj->toString ();
    }
}

std::vector<int>
MainWindow::get_selected_indices ()
{
  std::vector<int> indices;
  auto paths = m_TreeView.get_selection ()->get_selected_rows ();
  for (const auto &path : paths)
    {
      auto iter = m_refTreeModel->get_iter (path);
      if (iter)
        {
          indices.push_back ((*iter)[m_Columns.col_id]);
        }
    }
  return indices;
}

void
MainWindow::on_selection_changed ()
{
  auto selected_rows = m_TreeView.get_selection ()->get_selected_rows ();
  bool has_selection = !selected_rows.empty ();

  m_ButtonIncSelected.set_sensitive (has_selection);
  m_ButtonDecSelected.set_sensitive (has_selection);
  m_ButtonDelete.set_sensitive (has_selection);

  if (has_selection)
    {
      m_LabelSelection.set_markup ("<b>Selected ("
                                   + std::to_string (selected_rows.size ())
                                   + " items)</b>");
    }
  else
    {
      m_LabelSelection.set_markup ("<b>Bulk Actions</b>");
    }
}

void
MainWindow::on_button_add_clicked ()
{
  int typeId = m_DropDownType.get_selected () + 1;
  try
    {
      long f = std::stol (
          m_EntryFirst.get_text ().empty () ? "0" : m_EntryFirst.get_text ());
      long s = std::stol (m_EntrySecond.get_text ().empty ()
                              ? "0"
                              : m_EntrySecond.get_text ());

      dataStorage_.push_back (
          Core::NumberFactory::create (static_cast<Core::PairType> (typeId),
                                       Core::First{ f }, Core::Second{ s }));

      storage_->saveAll (dataStorage_);
      refresh_list ();
    }
  catch (...)
    {
    }
}

void
MainWindow::on_button_adjust_selected (int val)
{
  auto indices = get_selected_indices ();
  for (int idx : indices)
    {
      dataStorage_[static_cast<std::size_t> (idx)]->increase (val);
    }
  storage_->saveAll (dataStorage_);
  refresh_list ();
}

void
MainWindow::on_button_delete_selected ()
{
  auto indices = get_selected_indices ();
  std::sort (indices.begin (), indices.end (), std::greater<int> ());

  for (int idx : indices)
    {
      dataStorage_.erase (dataStorage_.begin () + idx);
    }

  storage_->saveAll (dataStorage_);
  refresh_list ();
}

} // namespace Gui
