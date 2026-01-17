#include "core/Factory.hpp"
#include "database/IStorage.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace Core;

void
displayMenu ()
{
  std::cout << "\n=== Lab 3: Console Manager ===\n"
            << "1. Add new Angle (Degrees)\n"
            << "2. Add new Angle (Radians)\n"
            << "3. Adjust one item\n"
            << "4. Adjust ALL\n"
            << "5. Delete an item\n"
            << "0. Exit\n"
            << "Selection: ";
}

void
displayList (const std::vector<std::unique_ptr<Pair> > &dataStorage)
{
  if (dataStorage.empty ())
    {
      std::cout << "List is empty.\n";
    }
  else
    {
      for (size_t i = 0; i < dataStorage.size (); ++i)
        {
          std::cout << i << ". ["
                    << (dataStorage[i]->getType () == PairType::Degrees
                            ? "Deg"
                            : "Rad")
                    << "] " << dataStorage[i]->toString () << "\n";
        }
    }
}

int
main ()
{
  auto storage = createStorage ("lab3.db");
  std::vector<std::unique_ptr<Pair> > dataStorage = storage->loadAll ();

  int choice = -1;
  while (choice != 0)
    {
      #ifdef _WIN32
        system("cls");
      #else
        system("clear");
      #endif
      displayList (dataStorage);
      displayMenu ();
      if (!(std::cin >> choice))
        {
          std::cin.clear ();
          std::cin.ignore (1000, '\n');
          continue;
        }

      switch (choice)
        {
        case 1:
        case 2:
          { // Add
            long f, s;
            std::cout << "Enter first value: ";
            std::cin >> f;
            std::cout << "Enter second value: ";
            std::cin >> s;

            auto type = (choice == 1) ? PairType::Degrees : PairType::Radians;
            dataStorage.push_back (
                NumberFactory::create (type, First{ f }, Second{ s }));
            storage->saveAll (dataStorage);
            std::cout << "Object added and saved.\n";
            break;
          }

        case 3:
          { // Adjust One
            int idx, val;
            std::cout << "Index to adjust: ";
            std::cin >> idx;
            if (idx >= 0 && idx < static_cast<int> (dataStorage.size ()))
              {
                std::cout << "Adjustment value: ";
                std::cin >> val;
                dataStorage[idx]->increase (val);
                storage->saveAll (dataStorage);
                std::cout << "Updated: " << dataStorage[idx]->toString ()
                          << "\n";
              }
            else
              {
                std::cout << "Invalid index.\n";
              }
            break;
          }

        case 4:
          { // Adjust All
            int val;
            std::cout << "Adjustment value for ALL: ";
            std::cin >> val;
            for (auto &obj : dataStorage)
              {
                obj->increase (val); // Virtual call
              }
            storage->saveAll (dataStorage);
            std::cout << "All objects updated.\n";
            break;
          }

        case 5:
          { // Delete
            int idx;
            std::cout << "Index to delete: ";
            std::cin >> idx;
            if (idx >= 0 && idx < static_cast<int> (dataStorage.size ()))
              {
                dataStorage.erase (dataStorage.begin () + idx);
                storage->saveAll (dataStorage);
                std::cout << "Item deleted.\n";
              }
            else
              {
                std::cout << "Invalid index.\n";
              }
            break;
          }
        }
    }

  std::cout << "Exiting Console Wrap...\n";
  return 0;
}
