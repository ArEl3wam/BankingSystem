#include <iostream>
#include "cli_state.h"
#include "cli_manager.h"

void MainMenuState::onEnter() {
  std::cout << "Welcome to the main menu!\n";
  std::cout << "1. Login\n";
  std::cout << "2. Add new user\n";
  std::cout << "3. Exit\n";
}

void MainMenuState::handleInput(const std::string &input) {
  if (input == "1") {
    cliManager->transitionToState(std::make_unique<LoginState>());
  } else if (input == "2") {
    cliManager->transitionToState(std::make_unique<AddNewUserState>());
  } else if (input == "3") {
    cliManager->transitionToState(std::make_unique<ExitState>());
  } else {
    std::cout << "Invalid input\n";
  }
}

