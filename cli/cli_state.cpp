#include "cli_state.h"
#include "cli_manager.h"
#include "database_interface.h"
#include "singleton.h"
#include <cassert>
#include <iostream>

// class MainMenuState
// --------------------------------------------
// --------------------------------------------

void MainMenuState::onEnter()
{
  std::cout << "Welcome to the main menu!\n";
  std::cout << "1. Login\n";
  std::cout << "2. Add new user\n";
  std::cout << "3. Exit\n";
}

void MainMenuState::handleInput(const std::string &input)
{
  if (input == "1")
  {
    auto loginState = std::make_shared<LoginState>(shared_from_this());
    cliManager->transitionToState(loginState);
  }
  else if (input == "2")
  {
    cliManager->transitionToState(
        std::make_shared<AddNewUserState>(shared_from_this()));
  }
  else if (input == "3")
  {
    cliManager->transitionToState(
        std::make_shared<ExitState>(shared_from_this()));
  }
  else { std::cout << "Invalid input\n"; }
}

// class ExitState
// --------------------------------------------
// --------------------------------------------

void ExitState::onEnter()
{
  std::cout << "Exiting...\n";
  std::exit(0);
}

void ExitState::handleInput(const std::string &input)
{
  // do nothing
  std::cout << input;
  assert(false);
}

// class LoginState
// --------------------------------------------
// --------------------------------------------

void LoginState::onEnter()
{
  switch (currentState)
  {
  case CurrentLoginState::WAITING_USERNAME:
    std::cout << "Enter username: \n";
    break;
  case CurrentLoginState::WAITING_PASSWORD:
    std::cout << "Enter password: \n";
    break;
  case CurrentLoginState::LOGGED_IN:
    std::cout << "Logged in successfully, Press enter to continue\n";
    break;
  case CurrentLoginState::FAILED_LOGIN:
    std::cout << "Failed to login,  press enter to back to main menu\n";
    break;
  }
}

void LoginState::handleInput(const std::string &input)
{

  switch (currentState)
  {
  case CurrentLoginState::WAITING_USERNAME:
    username = input;
    currentState = CurrentLoginState::WAITING_PASSWORD;
    cliManager->transitionToState(shared_from_this());
    break;
  case CurrentLoginState::WAITING_PASSWORD:
  {
    password = input;
    bool status;
    auto& database_interface = Singleton<SQLiteDatabaseInterface>::getInstance();
    status = database_interface.getUser(username, password, userId);
    if (!status)
    {
      currentState = CurrentLoginState::FAILED_LOGIN;
      std::cout << "Failed to login\n";
      cliManager->transitionToState(shared_from_this());
    }
    else
    {
      currentState = CurrentLoginState::LOGGED_IN;
      cliManager->transitionToState(shared_from_this());
    }
    break;
  }
  case CurrentLoginState::LOGGED_IN:
    cliManager->transitionToState(
        std::make_shared<UserMenuState>(shared_from_this(), userId));
    break;
  case CurrentLoginState::FAILED_LOGIN:
    cliManager->transitionToState(
        std::make_shared<MainMenuState>(shared_from_this()));
    break;
  }
}

// class UserMenuState
// --------------------------------------------
// --------------------------------------------

void UserMenuState::onEnter()
{
  std::cout << "Welcome, " << user->mGetNickName() << "!\n";
  std::cout << "1. View accounts\n";
  std::cout << "2. Add new Saving account\n";
  std::cout << "3. Add new Credit account\n";
  std::cout << "4. Transfer money\n";
  std::cout << "5. View Transactions\n";
}

void UserMenuState::handleInput(const std::string &input)
{
  if (input == "1")
  {
    cliManager->transitionToState(
        std::make_shared<ViewAccountsState>(shared_from_this(), user));
  }
  else if (input == "2")
  {
    cliManager->transitionToState(std::make_shared<AddNewAccountState>(
        shared_from_this(), user, AccountType::SAVING));
  }
  else if (input == "3")
  {
    cliManager->transitionToState(std::make_shared<AddNewAccountState>(
        shared_from_this(), user, AccountType::CREDIT));
  }
  else if (input == "4")
  {
    cliManager->transitionToState(
        std::make_shared<TransferMoneyState>(shared_from_this(), user));
  }
  else if (input == "5")
  {
    cliManager->transitionToState(
        std::make_shared<ViewTransactionsState>(shared_from_this(), user));
  }
  else { std::cout << "Invalid input\n"; }
};

// class ViewAccountsState
// --------------------------------------------
// --------------------------------------------

void ViewAccountsState::onEnter()
{
  std::cout << "Accounts:\n";
  for (const auto &account : user->mGetAccounts())
  {
    account->print();
  }
  std::cout << "Press enter to continue\n";
}

void ViewAccountsState::handleInput(const std::string &input)
{
  [[maybe_unused]] auto unused = input;
  cliManager->transitionToState(parentState);
}

// class AddNewUserState
// --------------------------------------------
// --------------------------------------------

void AddNewUserState::onEnter()
{
  switch (currentState)
  {
  case CurrentNewUserState::WAITING_NICKNAME:
    std::cout << "Enter nickname: \n";
    break;
  case CurrentNewUserState::WAITING_USERNAME:
    std::cout << "Enter username: \n";
    break;
  case CurrentNewUserState::WAITING_PASSWORD:
    std::cout << "Enter password: \n";
    break;
  case CurrentNewUserState::CREATED:
    std::cout << "User created successfully!, press enter to continue\n";
    break;
  case CurrentNewUserState::FAILED_LOGIN:
    std::cout << "Failed to login, press enter to back to main menu\n";
    break;
  }
}

void AddNewUserState::handleInput(const std::string &input)
{
  switch (currentState)
  {
  case CurrentNewUserState::WAITING_NICKNAME:
    nickname = input;
    currentState = CurrentNewUserState::WAITING_USERNAME;
    cliManager->transitionToState(shared_from_this());
    break;
  case CurrentNewUserState::WAITING_USERNAME:
    username = input;
    currentState = CurrentNewUserState::WAITING_PASSWORD;
    cliManager->transitionToState(shared_from_this());
    break;
  case CurrentNewUserState::WAITING_PASSWORD:
  {
    password = input;
    bool status;
    auto& database_interface = Singleton<SQLiteDatabaseInterface>::getInstance();
    status = database_interface.addUser(nickname, username, password, userId);
    if (status)
    {
      currentState = CurrentNewUserState::CREATED;
      cliManager->transitionToState(shared_from_this());
    }
    else
    {
      currentState = CurrentNewUserState::FAILED_LOGIN;
      cliManager->transitionToState(shared_from_this());
    }
    break;
  }
  case CurrentNewUserState::CREATED:
    cliManager->transitionToState(
        std::make_shared<UserMenuState>(shared_from_this(), userId));
    break;
  case CurrentNewUserState::FAILED_LOGIN:
    cliManager->transitionToState(
        std::make_shared<MainMenuState>(shared_from_this()));
    break;
  }
}

// class AddNewAccountState
// --------------------------------------------
// --------------------------------------------

void AddNewAccountState::onEnter() { std::cout << "Enter balance: \n"; }

void AddNewAccountState::handleInput(const std::string &input)
{
  double balance = std::stod(input);
  user->addNewAccount(balance, accountType);
  cliManager->transitionToState(parentState);
}

// class TransferMoneyState
// --------------------------------------------
// --------------------------------------------

bool TransferMoneyState::validateTransfer(double balance)
{
  if (balance < 0)
  {
    std::cout << "Invalid amount\n";
    return false;
  }

  if (sourceAcc == destAcc)
  {
    std::cout << "Source and destination account cannot be the same\n";
    return false;
  }

  for (const auto &account : user->mGetAccounts())
  {
    if (account->getAccNumber() == sourceAcc)
    {
      if (account->getBalance() < balance)
      {
        std::cout << "Insufficient balance\n";
        return false;
      }
      else { return true; }
    }
  }
  return false;
}

void TransferMoneyState::onEnter()
{
  switch (currentState)
  {
  case CurrentTransferState::WAITING_SOURCE_ACC:
    std::cout << "Enter source account number: \n";
    break;
  case CurrentTransferState::WAITING_DEST_ACC:
    std::cout << "Enter destination account number: \n";
    break;
  case CurrentTransferState::WAITING_AMOUNT:
    std::cout << "Enter amount: \n";
    break;
  case CurrentTransferState::TRANSFERRED:
    std::cout << "Transfered successfully, press enter to continue\n";
    break;
  case CurrentTransferState::FAILED_TRANSFER:
    std::cout << "Failed to transfer, press enter to continue\n";
    break;
  }
}

void TransferMoneyState::handleInput(const std::string &input)
{
  switch (currentState)
  {
  case CurrentTransferState::WAITING_SOURCE_ACC:
    sourceAcc = input;
    currentState = CurrentTransferState::WAITING_DEST_ACC;
    cliManager->transitionToState(shared_from_this());
    break;
  case CurrentTransferState::WAITING_DEST_ACC:
    destAcc = input;
    currentState = CurrentTransferState::WAITING_AMOUNT;
    cliManager->transitionToState(shared_from_this());
    break;
  case CurrentTransferState::WAITING_AMOUNT:
  {
    double amount = std::stod(input);
    bool status = validateTransfer(amount);
    if (!status)
    {
      currentState = CurrentTransferState::FAILED_TRANSFER;
      cliManager->transitionToState(shared_from_this());
      return;
    }
    status = user->transferMoney(sourceAcc, destAcc, amount);

    if (!status)
    {
      currentState = CurrentTransferState::FAILED_TRANSFER;
      cliManager->transitionToState(shared_from_this());
    }

    currentState = CurrentTransferState::TRANSFERRED;
    cliManager->transitionToState(shared_from_this());
    break;
  }
  case CurrentTransferState::TRANSFERRED:
    cliManager->transitionToState(parentState);
    break;
  case CurrentTransferState::FAILED_TRANSFER:
    cliManager->transitionToState(parentState);
    break;
  }
}

// class ViewTransactionsState
// --------------------------------------------
// --------------------------------------------

void ViewTransactionsState::onEnter()
{
  std::cout << "Transactions:\n";
  user->printTransactions();
  std::cout << "Press enter to continue\n";
}

void ViewTransactionsState::handleInput(const std::string &input)
{
  [[maybe_unused]] auto unused = input;
  cliManager->transitionToState(parentState);
}