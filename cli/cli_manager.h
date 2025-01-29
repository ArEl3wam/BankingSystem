#ifndef _CLI_PRINTER_H_
#define _CLI_PRINTER_H_
#include <memory>
#include <stack>
#include "cli_state.h"

// state context
class CliManager {
private:
  std::stack<std::unique_ptr<CliStateInterface>> stateStack;
  std::unique_ptr<CliStateInterface> currentState;

public:
  CliManager(std::unique_ptr<CliStateInterface> state) : currentState(std::move(state)) {}
  
  void transitionToState(std::unique_ptr<CliStateInterface> state);

  ~CliManager() = default;
};

#endif // _CLI_PRINTER_H_