#include "cli_manager.h"
#include <iostream>
#include <string>

void CliManager::printBackToPreviousMessage()
{
  // std::cout << "\x1B[2J";
  std::cout << "Press 'b' to go back.\n";
}

void CliManager::transitionToState(std::shared_ptr<CliBaseState> state)
{
  if (!state)
  {
    fprintf(stderr, "Invalid state transition\n");
    std::exit(0);
  }

  currentState = state;
  currentState->setManager(shared_from_this());
  if (currentState->parentState) printBackToPreviousMessage();
  currentState->onEnter();
}

void CliManager::goToPreviousState()
{
  if (!currentState || !currentState->parentState)
  {
    fprintf(stderr, "No previous state\n");
    std::exit(0);
  }

  currentState = currentState->parentState;
  currentState->onEnter();
}

void CliManager::handleInput(const std::string &input)
{
  if (input == "b")
  {
    goToPreviousState();
    return;
  }
  currentState->handleInput(input);
}