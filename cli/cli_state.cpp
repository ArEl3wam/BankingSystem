#include "cli_state.h"
#include "cli_manager.h"
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
    // cliManager->transitionToState(std::make_shared<AddNewUserState>(
    //     shared_from_this()));
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
  case CurrentState::WAITING_USERNAME:
    std::cout << "Enter username: \n";
    break;
  case CurrentState::WAITING_PASSWORD:
    std::cout << "Enter password: \n";
    break;
  case CurrentState::LOGGED_IN:
    std::cout << "Logged in successfully!\n";
    break;
  }
}

void LoginState::handleUsername(const std::string &input)
{
  username = input;
  currentState = CurrentState::WAITING_PASSWORD;
}

void LoginState::handlePassword(const std::string &input)
{
  password = input;
  currentState = CurrentState::LOGGED_IN;
  // TODO: Query database to check if username and password are correct
  // TODO: add input checkers
}

void LoginState::handleInput(const std::string &input)
{

  switch (currentState)
  {
  case CurrentState::WAITING_USERNAME:
    handleUsername(input);
    cliManager->transitionToState(shared_from_this());
    break;
  case CurrentState::WAITING_PASSWORD:
    handlePassword(input);
    cliManager->transitionToState(shared_from_this());
    break;
  case CurrentState::LOGGED_IN:
    cliManager->transitionToState(
        std::make_shared<UserMenuState>(shared_from_this()));
    break;
  }
}

// class UserMenuState
// --------------------------------------------
// --------------------------------------------

void UserMenuState::onEnter()
{
  std::cout << "Welcome, ay d7k!\n";
  std::cout << "1. View profile\n";
  std::cout << "2. Edit profile\n";
  std::cout << "3. Logout\n";
}

void UserMenuState::handleInput(const std::string &input)
{
  std::cout << input;
};