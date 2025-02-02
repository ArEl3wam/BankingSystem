#ifndef _CLI_STATE_H_
#define _CLI_STATE_H_

#include <memory>
#include <string>

class CliManager;
class CliBaseState: public std::enable_shared_from_this<CliBaseState>
{
protected:
  std::shared_ptr<CliManager> cliManager;
  std::shared_ptr<CliBaseState> parentState;

public:
  CliBaseState(std::shared_ptr<CliBaseState> parentState)
      : parentState(parentState)
  {
  }
  void setManager(std::shared_ptr<CliManager> manager) { cliManager = manager; }
  virtual void onEnter() = 0;
  virtual void handleInput(const std::string &input) = 0;
  virtual ~CliBaseState() = default;
  friend class CliManager;
};

class MainMenuState : public CliBaseState
{
public:
  MainMenuState(std::shared_ptr<CliBaseState> parentState)
      : CliBaseState(parentState)
  {
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~MainMenuState() = default;
};

class ExitState : public CliBaseState
{
public:
  ExitState(std::shared_ptr<CliBaseState> parentState)
      : CliBaseState(parentState)
  {
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~ExitState() = default;
};

class LoginState : public CliBaseState
{
  enum class CurrentState
  {
    WAITING_USERNAME,
    WAITING_PASSWORD,
    LOGGED_IN
  } currentState;
  std::string username;
  std::string password;
  void handleUsername(const std::string &input);
  void handlePassword(const std::string &input);

public:
  LoginState(std::shared_ptr<CliBaseState> parentState)
      : CliBaseState(parentState), currentState(CurrentState::WAITING_USERNAME),
        username(""), password("")
  {
    currentState = CurrentState::WAITING_USERNAME;
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~LoginState() = default;
};

class AddNewUserState : public CliBaseState
{
public:
  AddNewUserState(std::shared_ptr<CliBaseState> parentState)
      : CliBaseState(parentState)
  {
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~AddNewUserState() = default;
};

class UserMenuState : public CliBaseState
{
public:
  UserMenuState(std::shared_ptr<CliBaseState> parentState)
      : CliBaseState(parentState)
  {
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~UserMenuState() = default;
};

class ViewAccountsState : public CliBaseState
{
public:
  ViewAccountsState(std::shared_ptr<CliBaseState> parentState)
      : CliBaseState(parentState)
  {
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~ViewAccountsState() = default;
};

class DepositState : public CliBaseState
{
public:
  DepositState(std::shared_ptr<CliBaseState> parentState)
      : CliBaseState(parentState)
  {
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~DepositState() = default;
};

class WithdrawState : public CliBaseState
{
public:
  WithdrawState(std::shared_ptr<CliBaseState> parentState)
      : CliBaseState(parentState)
  {
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~WithdrawState() = default;
};

#endif // _CLI_STATE_H_