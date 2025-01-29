#ifndef _CLI_STATE_H_
#define _CLI_STATE_H_

#include <memory>
#include <string>

class CliManager;
class CliStateInterface {
protected:
  std::shared_ptr<CliManager> cliManager;

public:
  CliStateInterface();
  virtual void onEnter() = 0;
  virtual void handleInput(const std::string &input) = 0;
  void setManager(std::shared_ptr<CliManager> manager) { cliManager = manager; }
  virtual ~CliStateInterface() = default;
};

class MainMenuState : public CliStateInterface {
public:
  MainMenuState() = default;
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~MainMenuState() = default;
};

class ExitState : public CliStateInterface {
public:
  ExitState() = default;
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~ExitState() = default;
};

class LoginState : public CliStateInterface {
public:
  LoginState() = default;
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~LoginState() = default;
};

class AddNewUserState : public CliStateInterface {
public:
  AddNewUserState() = default;
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~AddNewUserState() = default;
};

class UserMenuState : public CliStateInterface {
public:
  UserMenuState() = default;
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~UserMenuState() = default;
};

class ViewAccountsState : public CliStateInterface {
public:
  ViewAccountsState() = default;
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~ViewAccountsState() = default;
};

class DepositState : public CliStateInterface {
public:
  DepositState() = default;
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~DepositState() = default;
};

class WithdrawState : public CliStateInterface {
public:
  WithdrawState() = default;
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~WithdrawState() = default;
};

#endif // _CLI_STATE_H_