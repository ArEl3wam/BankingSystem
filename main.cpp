#include "cli_manager.h"
#include "cli_state.h"
#include <iostream>
#include "sqlite3.h"


int main()
{

    // sqlite3* db;
    // int rc = sqlite3_open("bank.db", &db);
    
    // if (rc != SQLITE_OK) {
    //     // Handle error
    // }
    
    // // Use the database...
    
    // sqlite3_close(db);
    // return 0;

  auto manager = std::make_shared<CliManager>();
  manager->transitionToState(std::make_shared<MainMenuState>(nullptr));
  while (true)
  {
    std::string input{};
    std::getline(std::cin, input);
    manager->handleInput(input);
  }
  return 0;
}