#pragma once

#include "printable.h"
#include <string>

class BaseAccount : public Printable
{
protected:
  std::string accNumber;
  double balance;

public:
  BaseAccount(std::string xAccNumber, double balance)
      : accNumber(xAccNumber), balance(balance)
  {
  }
  const std::string &getAccNumber() const { return accNumber; }
  double getBalance() const { return balance; }
  void setBalance(double balance);
  void deposit(double amount);
  void withdraw(double amount);
  virtual ~BaseAccount() = default;
};

class SavingAccount : public BaseAccount
{

public:
  SavingAccount(std::string xAccNumber)
      : BaseAccount(xAccNumber, 5000)
  {
  }
  SavingAccount(std::string xAccNumber, double balance)
      : BaseAccount(xAccNumber, balance)
  {
  }
  void print() const override;
};

class CreditAccount : public BaseAccount
{
private:
  double dInterestRate;
  double dUserCreditScore;
  double dOverdraftLimit;

public:
  CreditAccount(std::string xAccNumber)
      : BaseAccount(xAccNumber, 20000), dInterestRate(1.25),
        dUserCreditScore(1.2), dOverdraftLimit(balance * dUserCreditScore)
  {
  }
  CreditAccount(std::string xAccNumber, double balance, double userCreditScore)
      : BaseAccount(xAccNumber, balance), dInterestRate(1.25),
        dUserCreditScore(userCreditScore),
        dOverdraftLimit(balance * userCreditScore)
  {
  }

  CreditAccount(std::string xAccNumber, double balance)
      : BaseAccount(xAccNumber, balance), dInterestRate(1.25),
        dUserCreditScore(1.2), dOverdraftLimit(balance * dUserCreditScore)
  {
  }

  void setOverdraftLimit(double overdraftLimit)
  {
    dOverdraftLimit = overdraftLimit;
  }
  void setInterestRate(double interestRate) { dInterestRate = interestRate; }
  void setUserCreditScore(double userCreditScore)
  {
    dUserCreditScore = userCreditScore;
  }

  double getOverdraftLimit() const { return dOverdraftLimit; }
  double getInterestRate() const { return dInterestRate; }
  double getUserCreditScore() const { return dUserCreditScore; }

  void print() const override;
};