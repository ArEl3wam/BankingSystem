#include "user.h"
#include "database_interface.h"
#include "singleton.h"

User::User(int id)
{
  auto& database_interface = Singleton<SQLiteDatabaseInterface>::getInstance();
  UserData userData{};
  database_interface.getUserData(id, userData);
  dId = userData.id;
  dNickname = userData.nickname;
  dUsername = userData.username;
  for (const auto &acc : userData.accounts)
  {
    if (acc.accNumber[0] == 'S')
    {
      dAccounts.push_back(
          std::make_shared<SavingAccount>(acc.accNumber, acc.balance));
    }
    else if (acc.accNumber[0] == 'C')
    {
      dAccounts.push_back(
          std::make_shared<CreditAccount>(acc.accNumber, acc.balance));
    }
  }
}

void User::addNewAccount(double balance, AccountType accountType)
{
  auto& database_interface = Singleton<SQLiteDatabaseInterface>::getInstance();
  std::string accNumber =
      std::to_string(dId) + std::to_string(dAccounts.size());
  if (accountType == AccountType::SAVING)
  {
    accNumber.insert(0, "S");
    dAccounts.push_back(std::make_shared<SavingAccount>(accNumber, balance));
  }
  else if (accountType == AccountType::CREDIT)
  {
    accNumber.insert(0, "C");
    dAccounts.push_back(std::make_shared<CreditAccount>(accNumber, balance));
  }
  database_interface.addAccount(dId, accNumber, balance);
}

bool User::deposit(const std::string &accNumber, double amount)
{
  auto& database_interface = Singleton<SQLiteDatabaseInterface>::getInstance();
  bool status = database_interface.deposit(accNumber, amount);

  for (auto &acc : dAccounts)
  {
    if (acc->getAccNumber() == accNumber)
    {
      acc->deposit(amount);
      break;
    }
  }

  return status;
}

bool User::withdraw(const std::string &accNumber, double amount)
{
  auto& database_interface = Singleton<SQLiteDatabaseInterface>::getInstance();
  bool status = database_interface.withdraw(accNumber, amount);
  for(auto &acc : dAccounts)
  {
    if(acc->getAccNumber() == accNumber)
    {
      acc->withdraw(amount);
      break;
    }
  }
  return status;
}

bool User::transferMoney(const std::string &sourceAcc,
                         const std::string &destAcc, double amount)
{
  auto& database_interface = Singleton<SQLiteDatabaseInterface>::getInstance();
  bool status = database_interface.transferMoney(sourceAcc, destAcc, amount);
  for(auto &acc : dAccounts)
  {
    if(acc->getAccNumber() == sourceAcc)
    {
      acc->withdraw(amount);
    }
    if(acc->getAccNumber() == destAcc)
    {
      acc->deposit(amount);
    }
  }
  return status;
}

void User::addAccounts(const UserData &userData)
{
  for (const auto &acc : userData.accounts)
  {
    if (acc.accNumber[0] == 'S')
    {
      dAccounts.push_back(
          std::make_shared<SavingAccount>(acc.accNumber, acc.balance));
    }
    else if (acc.accNumber[0] == 'C')
    {
      dAccounts.push_back(
          std::make_shared<CreditAccount>(acc.accNumber, acc.balance));
    }
  }
}

void User::print() const
{
  std::cout << "User: " << dNickname << "\n";
  std::cout << "Username: " << dUsername << "\n";
  std::cout << (dAccounts.size() ? "Accounts: "
                                 : "You still don`t have any account")
            << "\n";
  for (const auto &acc : dAccounts)
  {
    acc->print();
  }
}

void User::printTransactions() const
{
  std::vector<TransactionData> transactions{};
  auto& database_interface = Singleton<SQLiteDatabaseInterface>::getInstance();
  database_interface.getTransactionHistory(dId, transactions);

  for (const auto &transcation : transactions)
  {
    std::cout << "Transaction ID: " << transcation.id << "\n";
    std::cout << "Type: "
              << (transcation.type == TransactionType::DEPOSIT ? "Deposit"
                                                               : "Withdraw")
              << "\n";
    std::cout << "Amount: " << transcation.amount << "\n";
    std::cout << "Source Account: " << transcation.sourceAcc << "\n";
    std::cout << "Destination Account: " << transcation.destAcc << "\n";
    std::cout << "Timestamp: " << transcation.timestamp << "\n";
    std::cout << "--------------------------------------------\n";
  }
}
