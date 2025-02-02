#ifndef _CLI_PRINTER_H_
#define _CLI_PRINTER_H_
#include "cli_state.h"
#include <memory>

class CliManager: public std::enable_shared_from_this<CliManager> 
{
private:
  std::shared_ptr<CliBaseState> currentState;
  void printBackToPreviousMessage();

public:
  CliManager() = default;

  void transitionToState(std::shared_ptr<CliBaseState> state);
  void goToPreviousState();
  void handleInput(const std::string &input);

  ~CliManager() = default;
};

#endif // _CLI_PRINTER_H_