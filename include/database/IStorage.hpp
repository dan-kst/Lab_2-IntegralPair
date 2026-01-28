#ifndef I_STORAGE_HPP
#define I_STORAGE_HPP

#include "core/Pair.hpp"
#include <memory>
#include <string>
#include <vector>

namespace Core
{

/// @brief Abstract interface for data persistence.
class [[nodiscard]] IStorage
{
public:
  virtual ~IStorage () = default;

  /// @brief Saves the entire collection to persistence.
  virtual void saveAll (const std::vector<std::unique_ptr<Pair> > &items) = 0;

  /// @brief Loads all objects from persistence.
  virtual auto loadAll () -> std::vector<std::unique_ptr<Pair> > = 0;
};

/// @brief Factory function to create a storage backend.
[[nodiscard]] auto createStorage (const std::string &path)
    -> std::unique_ptr<IStorage>;
} // namespace Core

#endif // STORAGE_HPP
