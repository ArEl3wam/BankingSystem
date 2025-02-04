#include "account.h"
#include <iostream>

void BaseAccount::setBalance(double balance) { this->balance = balance; }

void BaseAccount::deposit(double amount) { balance += amount; }

void BaseAccount::withdraw(double amount)
{
  if (amount > balance)
  {
    std::cerr << "Insufficient balance\n";
    return;
  }
  balance -= amount;
}


void SavingAccount::print() const
{

  std::cout << "Saving Account\n";
  std::cout << "Account Number: " << accNumber << std::endl;
  std::cout << "Balance: " << balance << std::endl;
  std::cout << "-----------------------------------\n";
}


void CreditAccount::print() const
{
  std::cout << "Credit Account\n";
  std::cout << "Account Number: " << accNumber << std::endl;
  std::cout << "Balance: " << balance << std::endl;
  std::cout << "Interest Rate: " << dInterestRate << std::endl;
  std::cout << "Credit Score: " << dUserCreditScore << std::endl;
  std::cout << "Overdraft Limit: " << dOverdraftLimit << std::endl;
  std::cout << "-----------------------------------\n";
}
