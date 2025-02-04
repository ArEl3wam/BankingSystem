#pragma once

#include <string>
#include <vector>

struct AccountData
{
  int id;
  std::string accNumber;
  double balance;
};

struct UserData
{
  int id;
  std::string nickname;
  std::string username;
  std::string password;
  std::vector<AccountData> accounts;
};

enum class AccountType
{
  SAVING,
  CREDIT
};

enum class TransactionType
{
  DEPOSIT,
  WITHDRAW,
  TRANSFER
};

struct TransactionData
{
  int id;
  TransactionType type;
  double amount;
  std::string sourceAcc;
  std::string destAcc;
  std::string timestamp;
};
