#include "cli_manager.h"
#include "cli_state.h"
#include <iostream>


int main()
{
  auto manager = std::make_shared<CliManager>();
  manager->transitionToState(std::make_shared<MainMenuState>(nullptr));
  while (true)
  {
    std::string input{};
    std::getline(std::cin, input);
    manager->handleInput(input);
  }
  // return 0;
}