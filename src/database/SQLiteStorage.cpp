#include "database/SQLiteStorage.hpp"
#include "core/Factory.hpp"
#include <sqlite3.h>
#include <stdexcept>

namespace Core
{

SQLiteStorage::SQLiteStorage (std::string path) : dbPath_ (std::move (path))
{
  if (sqlite3_open (dbPath_.c_str (), &db_) != SQLITE_OK)
    {
      throw std::runtime_error ("Could not open database");
    }
  // Create table if it doesn't exist
  // Store type_id, first_val, and second_val
  executeQuery ("CREATE TABLE IF NOT EXISTS pairs ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "type_id INTEGER NOT NULL,"
                "first_val INTEGER NOT NULL,"
                "second_val INTEGER NOT NULL);");
}

SQLiteStorage::~SQLiteStorage ()
{
  if (db_)
    sqlite3_close (db_);
}

void
SQLiteStorage::executeQuery (const std::string &query)
{
  char *errMsg = nullptr;
  if (sqlite3_exec (db_, query.c_str (), nullptr, nullptr, &errMsg)
      != SQLITE_OK)
    {
      std::string err = errMsg;
      sqlite3_free (errMsg);
      throw std::runtime_error ("SQLite Error: " + err);
    }
}

void
SQLiteStorage::saveAll (const std::vector<std::unique_ptr<Pair> > &items)
{
  executeQuery ("BEGIN TRANSACTION;");
  executeQuery ("DELETE FROM pairs;"); // Clear old state

  for (const auto &item : items)
    {
      std::string query
          = "INSERT INTO pairs (type_id, first_val, second_val) VALUES ("
            + std::to_string (static_cast<int> (item->getType ())) + ", "
            + std::to_string (static_cast<std::intmax_t> (item->getFirst ()))
            + ", "
            + std::to_string (static_cast<std::intmax_t> (item->getSecond ()))
            + ");";
      executeQuery (query);
    }

  executeQuery ("COMMIT;");
}

auto
SQLiteStorage::loadAll () -> std::vector<std::unique_ptr<Pair> >
{
  std::vector<std::unique_ptr<Pair> > items;
  sqlite3_stmt *stmt;
  std::string query = "SELECT type_id, first_val, second_val FROM pairs;";

  if (sqlite3_prepare_v2 (db_, query.c_str (), -1, &stmt, nullptr)
      != SQLITE_OK)
    {
      throw std::runtime_error ("Failed to fetch data");
    }

  while (sqlite3_step (stmt) == SQLITE_ROW)
    {
      int type = sqlite3_column_int (stmt, 0);
      int f = sqlite3_column_int (stmt, 1);
      int s = sqlite3_column_int (stmt, 2);

      items.push_back (
          NumberFactory::create (static_cast<PairType> (type),
                                 First{ static_cast<std::intmax_t> (f) },
                                 Second{ static_cast<std::intmax_t> (s) }));
    }

  sqlite3_finalize (stmt);
  return items;
}

auto
createStorage (const std::string &path) -> std::unique_ptr<IStorage>
{
  return std::make_unique<SQLiteStorage> (path);
}

} // namespace Core
