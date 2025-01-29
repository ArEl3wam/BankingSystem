#include "cli_manager.h"

void CliManager::transitionToState(std::unique_ptr<CliStateInterface> state) {
  if (!state) {
    fprintf(stderr, "Invalid state transition\n");
    std::exit(0);
  }

  if (currentState)
    stateStack.push(std::move(currentState));

  currentState = std::move(state);
  currentState->onEnter();
  
}