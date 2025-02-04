#pragma once

#include "common.h"
#include "sqlite3.h"
#include <iostream>
#include <vector>

class BaseDatabaseInterface
{
protected:
  virtual void connect(const std::string xDatabaseName = "") = 0;
  virtual void disconnect() = 0;
  virtual bool createTables() = 0;

public:
  virtual bool addUser(const std::string &nickname, const std::string &username,
                       const std::string &password, int &usedId) = 0;
  virtual bool addAccount(int userId, const std::string &accNumber,
                          double balance) = 0;

  virtual bool getUser(const std::string &username, const std::string &password,
                       int &userId) = 0;

  virtual bool getUserData(int userId, UserData &userData) = 0;

  virtual bool getUserIdFromAccount(const std::string &accNumber,
                                    int &userId) = 0;

  virtual bool isValidUserId(int userId) = 0;

  virtual bool getAccount(int userId, const std::string &accNumber) = 0;

  virtual bool deposit(const std::string &accNumber, double amount) = 0;

  virtual bool withdraw(const std::string &accNumber, double amount) = 0;

  virtual bool transferMoney(const std::string &sourceAcc,
                             const std::string &destAcc, double amount) = 0;

  virtual bool insertTransaction(int userId, TransactionType type,
                                 double amount, const std::string &sourceAcc,
                                 const std::string &destAcc) = 0;

  virtual bool
  getTransactionHistory(int userId,
                        std::vector<TransactionData> &transactions) = 0;
  virtual ~BaseDatabaseInterface() = default;
};

class SQLiteDatabaseInterface : public BaseDatabaseInterface
{

private:
  sqlite3 *db;
  void connect(const std::string xDatabaseName) override;
  void disconnect() override;
  bool createTables() override;
  bool getUserAccounts(int userId, std::vector<AccountData> &accounts);

public:
  SQLiteDatabaseInterface() : SQLiteDatabaseInterface("bank.db") {}

  SQLiteDatabaseInterface(const std::string xDatabaseName)
      : db(nullptr)
  {
    connect(xDatabaseName);
    createTables();
  }

  void reset()
  {
    disconnect();
    connect("bank.db");
    if (db) createTables();
  }

  bool addUser(const std::string &nickname, const std::string &username,
               const std::string &password, int &userId) override;

  bool addAccount(int userId, const std::string &accNumber,
                  double balance) override;

  bool getUser(const std::string &username, const std::string &password,
               int &userId) override;

  bool getUserData(int userId, UserData &userData) override;

  bool getUserIdFromAccount(const std::string &accNumber, int &userId) override;

  bool isValidUserId(int userId) override;

  bool getAccount(int userId, const std::string &accNumber) override;

  bool transferMoney(const std::string &sourceAcc, const std::string &destAcc,
                     double amount) override;

  bool deposit(const std::string &accNumber, double amount) override;

  bool withdraw(const std::string &accNumber, double amount) override;

  bool insertTransaction(int userId, TransactionType type, double amount,
                         const std::string &sourceAcc,
                         const std::string &destAcc) override;

  bool
  getTransactionHistory(int userId,
                        std::vector<TransactionData> &transactions) override;

  ~SQLiteDatabaseInterface() { disconnect(); }
};