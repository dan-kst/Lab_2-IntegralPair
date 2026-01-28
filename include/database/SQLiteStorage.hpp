#include "core/Factory.hpp"
#include "database/IStorage.hpp"
#include <sqlite3.h>
#include <stdexcept>

namespace Core
{
class SQLiteStorage : public IStorage
{
private:
  sqlite3 *db_ = nullptr;
  std::string dbPath_;
  void executeQuery (const std::string &query);

public:
  explicit SQLiteStorage (std::string path);
  ~SQLiteStorage () override;
  void saveAll (const std::vector<std::unique_ptr<Pair> > &items) override;
  std::vector<std::unique_ptr<Pair> > loadAll () override;
};
} // namespace Core
