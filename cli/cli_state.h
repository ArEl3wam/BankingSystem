#pragma once

#include "common.h"
#include "user.h"
#include <memory>
#include <string>

class CliManager;
class CliBaseState : public std::enable_shared_from_this<CliBaseState>
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
  enum class CurrentLoginState
  {
    WAITING_USERNAME,
    WAITING_PASSWORD,
    LOGGED_IN,
    FAILED_LOGIN
  } currentState;
  std::string username;
  std::string password;
  int userId;

public:
  LoginState(std::shared_ptr<CliBaseState> parentState)
      : CliBaseState(parentState),
        currentState(CurrentLoginState::WAITING_USERNAME), username(""),
        password(""), userId(-1)
  {
    currentState = CurrentLoginState::WAITING_USERNAME;
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~LoginState() = default;
};

class AddNewUserState : public CliBaseState
{
  enum class CurrentNewUserState
  {
    WAITING_NICKNAME,
    WAITING_USERNAME,
    WAITING_PASSWORD,
    CREATED,
    FAILED_LOGIN
  } currentState;

  std::string nickname;
  std::string username;
  std::string password;
  int userId;

public:
  AddNewUserState(std::shared_ptr<CliBaseState> parentState)
      : CliBaseState(parentState),
        currentState(CurrentNewUserState::WAITING_NICKNAME), nickname(""),
        username(""), password(""), userId(-1)
  {
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~AddNewUserState() = default;
};

class UserMenuState : public CliBaseState
{
  std::shared_ptr<User> user;
  int dUserId;

public:
  UserMenuState(std::shared_ptr<CliBaseState> parentState, int xUserId)
      : CliBaseState(parentState), user(std::make_shared<User>(xUserId)),
        dUserId(xUserId)
  {
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~UserMenuState() = default;
};

class ViewAccountsState : public CliBaseState
{
  std::shared_ptr<User> user;

public:
  ViewAccountsState(std::shared_ptr<CliBaseState> parentState,
                    std::shared_ptr<User> xUser)
      : CliBaseState(parentState), user(xUser)
  {
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~ViewAccountsState() = default;
};

class AddNewAccountState : public CliBaseState
{
  std::shared_ptr<User> user;
  AccountType accountType;

public:
  AddNewAccountState(std::shared_ptr<CliBaseState> parentState,
                     std::shared_ptr<User> xUser, AccountType xAccountType)
      : CliBaseState(parentState), user(xUser), accountType(xAccountType)
  {
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~AddNewAccountState() = default;
};

class TransferMoneyState : public CliBaseState
{
  std::shared_ptr<User> user;

  enum class CurrentTransferState
  {
    WAITING_SOURCE_ACC,
    WAITING_DEST_ACC,
    WAITING_AMOUNT,
    TRANSFERRED,
    FAILED_TRANSFER
  } currentState;
  std::string sourceAcc;
  std::string destAcc;
  double amount;
  bool validateTransfer(double amount);

public:
  TransferMoneyState(std::shared_ptr<CliBaseState> parentState,
                     std::shared_ptr<User> xUser)
      : CliBaseState(parentState), user(xUser),
        currentState(CurrentTransferState::WAITING_SOURCE_ACC), sourceAcc(""),
        destAcc(""), amount(0)
  {
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~TransferMoneyState() = default;
};

class ViewTransactionsState : public CliBaseState
{
  std::shared_ptr<User> user;

public:
  ViewTransactionsState(std::shared_ptr<CliBaseState> parentState,
                        std::shared_ptr<User> xUser)
      : CliBaseState(parentState), user(xUser)
  {
  }
  void onEnter() override;
  void handleInput(const std::string &input) override;
  virtual ~ViewTransactionsState() = default;
};
