#include "core/Factory.hpp"
#include "crow.h"
#include <memory>
#include <string>
#include <vector>

using namespace Core;

int
main ()
{
  crow::SimpleApp app;
  std::vector<std::unique_ptr<Pair> > dataStorage;

  // Initial Seed Data
  dataStorage.push_back (
      NumberFactory::create (PairType::Degrees, First{ 90 }, Second{ 15 }));
  dataStorage.push_back (
      NumberFactory::create (PairType::Radians, First{ 1 }, Second{ 570 }));

  CROW_ROUTE (app, "/") ([] (const crow::request &, crow::response &res) {
    res.set_static_file_info ("src/web/index.html");
    res.end ();
  });

  /// @route GET /api/numbers
  CROW_ROUTE (app, "/api/numbers")
  ([&dataStorage] () {
    std::vector<crow::json::wvalue> jsonList;
    for (const auto &obj : dataStorage)
      {
        crow::json::wvalue item;
        const auto type = obj->getType ();
        item["type"] = (type == PairType::Degrees ? "Degrees" : "Radians");
        item["display"] = obj->toString ();
        item["first"] = static_cast<std::intmax_t> (obj->getFirst ());
        item["second"] = static_cast<std::intmax_t> (obj->getSecond ());
        jsonList.push_back (std::move (item));
      }
    return crow::json::wvalue (jsonList);
  });

  /// @route POST /api/adjust/<int>/<int>
  CROW_ROUTE (app, "/api/adjust/<int>/<int>")
      .methods (crow::HTTPMethod::POST,
                crow::HTTPMethod::GET) ([&dataStorage] (int index, int val) {
        if (index < 0 || index >= static_cast<int> (dataStorage.size ()))
          {
            return crow::response (404, "Object index not found");
          }
        dataStorage[static_cast<std::size_t> (index)]->increase (val);
        return crow::response (
            200, dataStorage[static_cast<std::size_t> (index)]->toString ());
      });

  app.port (18080).loglevel (crow::LogLevel::Debug).multithreaded ().run ();
}
