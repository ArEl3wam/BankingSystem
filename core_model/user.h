#pragma once
#include "account.h"
#include "common.h"
#include <memory>
#include <string>
#include <vector>

class User : public Printable
{

  int dId;
  std::string dNickname;
  std::string dUsername;
  std::vector<std::shared_ptr<BaseAccount>> dAccounts;
  void addAccounts(const UserData &userData);

public:
  User(int id, std::string nickname, std::string username)
      : dId(id), dNickname(nickname), dUsername(username), dAccounts()
  {
  }
  User(int id);
  int mGetId() const { return dId; }
  std::string mGetNickName() const { return dNickname; }
  std::string mGetUserName() const { return dUsername; }
  const std::vector<std::shared_ptr<BaseAccount>> &mGetAccounts() const
  {
    return dAccounts;
  }
  void addNewAccount(double balance, AccountType accountType);
  bool withdraw(const std::string &accNumber, double amount);
  bool deposit(const std::string &accNumber, double amount);
  bool transferMoney(const std::string &sourceAcc, const std::string &destAcc, double amount);
  void print() const override;
  void printTransactions() const;
};