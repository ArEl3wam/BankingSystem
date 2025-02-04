#include "database_interface.h"

void SQLiteDatabaseInterface::connect(const std::string xDatabaseName)
{
  // Close existing connection if any
  if (db)
  {
    sqlite3_close(db);
    db = nullptr;
  }

  int rc = sqlite3_open(xDatabaseName.c_str(), &db);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Can't open database: " << sqlite3_errstr(rc) << std::endl;
    db = nullptr; // Ensure db is NULL on failure
    return;
  }

  // Enable foreign keys
  char *errMsg = nullptr;
  rc = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to enable foreign keys: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    sqlite3_close(db);
    db = nullptr;
    return;
  }

  // std::cout << "Database opened successfully" << std::endl;
}

bool SQLiteDatabaseInterface::createTables()
{
  std::string sql = "CREATE TABLE IF NOT EXISTS users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nickname TEXT NOT NULL,"
                    "username TEXT NOT NULL,"
                    "password TEXT NOT NULL);";
  char *errMsg = nullptr;
  
  int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &errMsg);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to create users table: " << errMsg << std::endl;
    return false;
  }

  sql = "CREATE TABLE IF NOT EXISTS accounts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "user_id INTEGER NOT NULL,"
        "acc_number TEXT NOT NULL,"
        "balance REAL NOT NULL,"
        "FOREIGN KEY(user_id) REFERENCES users(id));";
  rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &errMsg);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to create accounts table: " << errMsg << std::endl;
    return false;
  }

  sql = "CREATE TABLE IF NOT EXISTS transactions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "user_id INTEGER NOT NULL,"
        "type TEXT NOT NULL,"
        "amount REAL NOT NULL,"
        "source_acc TEXT,"
        "dest_acc TEXT,"
        "timestamp TEXT NOT NULL,"
        "FOREIGN KEY(user_id) REFERENCES users(id));";
  rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &errMsg);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to create transactions table: " << errMsg << std::endl;
    return false;
  }

  // std::cout << "Tables created successfully" << std::endl;
  return true;
}

bool SQLiteDatabaseInterface::getAccount(int userId,
                                         const std::string &accNumber)
{
  std::string sql = "SELECT id, acc_number, balance FROM accounts WHERE "
                    "user_id = ? AND acc_number = ?";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to fetch account: " << sqlite3_errmsg(db) << std::endl;
    // return false;
  }

  sqlite3_bind_int(stmt, 1, userId);
  sqlite3_bind_text(stmt, 2, accNumber.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW)
  {
    // You can process the account data here
    int accId = sqlite3_column_int(stmt, 0);
    const char *accNum =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    double balance = sqlite3_column_double(stmt, 2);

    std::cout << "Account ID: " << accId << ", Account Number: " << accNum
              << ", Balance: " << balance << std::endl;
    sqlite3_finalize(stmt);
    return true;
  }
  else
  {
    std::cerr << "Account not found!" << std::endl;
    sqlite3_finalize(stmt);
    return false;
  }
}

bool SQLiteDatabaseInterface::addAccount(int userId,
                                         const std::string &accNumber,
                                         double balance)
{
  if (!db)
  {
    std::cerr << "Database not connected!" << std::endl;
    return false;
  }
  std::string sql =
      "INSERT INTO accounts (user_id, acc_number, balance) VALUES (?, ?, ?)";
  sqlite3_stmt *stmt;
  // std:: cout << "rc: " << rc << std::endl;
  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  std::cout << "rc: " << rc << std::endl;
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to insert account: " << sqlite3_errmsg(db)
              << std::endl;
    return false;
  }

  sqlite3_bind_int(stmt, 1, userId);
  sqlite3_bind_text(stmt, 2, accNumber.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_double(stmt, 3, balance);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE)
  {
    std::cerr << "Failed to add account!" << std::endl;
    sqlite3_finalize(stmt);
    return false;
  }

  std::cout << "Account added successfully" << std::endl;
  sqlite3_finalize(stmt);
  return true;
}

bool SQLiteDatabaseInterface::getUser(const std::string &username,
                                      const std::string &password, int &userId)
{
  std::string sql = "SELECT id FROM users WHERE username = ? AND password = ?";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to fetch user: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW)
  {
    userId = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return true;
  }
  else
  {
    std::cerr << "User not found!" << std::endl;
    sqlite3_finalize(stmt);
    return false;
  }
}

bool SQLiteDatabaseInterface::getUserAccounts(
    int userId, std::vector<AccountData> &accounts)
{
  std::string sql = "SELECT id, acc_number, balance FROM accounts WHERE "
                    "user_id = ?";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to fetch accounts: " << sqlite3_errmsg(db)
              << std::endl;
    return false;
  }

  sqlite3_bind_int(stmt, 1, userId);

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
  {
    AccountData account;
    account.id = sqlite3_column_int(stmt, 0);
    account.accNumber =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    account.balance = sqlite3_column_double(stmt, 2);
    accounts.push_back(account);
  }

  if (rc != SQLITE_DONE)
  {
    std::cerr << "Failed to fetch accounts!" << std::endl;
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);
  return true;
}

bool SQLiteDatabaseInterface::getUserData(int userId, UserData &userData)
{
  std::string sql = "SELECT id, nickname, username FROM users WHERE id = ?";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to fetch user: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  sqlite3_bind_int(stmt, 1, userId);

  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW)
  {
    userData.id = sqlite3_column_int(stmt, 0);
    userData.nickname =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    userData.username =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
    sqlite3_finalize(stmt);
    return getUserAccounts(userId, userData.accounts);
  }
  else
  {
    std::cerr << "User not found!" << std::endl;
    sqlite3_finalize(stmt);
    return false;
  }
}

bool SQLiteDatabaseInterface::getUserIdFromAccount(const std::string &accNumber,
                                                   int &userId)
{
  std::string sql = "SELECT user_id FROM accounts WHERE acc_number = ?";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to fetch user: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  sqlite3_bind_text(stmt, 1, accNumber.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW)
  {
    userId = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return true;
  }
  else
  {
    std::cerr << "User not found!" << std::endl;
    sqlite3_finalize(stmt);
    return false;
  }
}

bool SQLiteDatabaseInterface::isValidUserId(int xId)
{
  std::string sql = "SELECT id FROM users WHERE id = ?";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to fetch user: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  sqlite3_bind_int(stmt, 1, xId);

  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW)
  {
    sqlite3_finalize(stmt);
    return true;
  }
  else
  {
    std::cerr << "User not found!" << std::endl;
    sqlite3_finalize(stmt);
    return false;
  }
}

bool SQLiteDatabaseInterface::addUser(const std::string &nickname,
                                      const std::string &username,
                                      const std::string &password, int &userId)
{
  std::string sql =
      "INSERT INTO users (nickname, username, password) VALUES (?, ?, ?)";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to insert user: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  sqlite3_bind_text(stmt, 1, nickname.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, password.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE)
  {
    std::cerr << "Failed to add user!" << std::endl;
    sqlite3_finalize(stmt);
    return false;
  }
  userId = sqlite3_last_insert_rowid(db);

  std::cout << "User added successfully" << std::endl;
  sqlite3_finalize(stmt);
  return true;
}

bool SQLiteDatabaseInterface::withdraw(const std::string &accNumber,
                                       double amount)
{
  std::string sql = "UPDATE accounts SET balance = balance - ? WHERE "
                    "acc_number = ?";

  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to withdraw: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  sqlite3_bind_double(stmt, 1, amount);
  sqlite3_bind_text(stmt, 2, accNumber.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE)
  {
    std::cerr << "Failed to withdraw!" << std::endl;
    sqlite3_finalize(stmt);
    return false;
  }

  std::cout << "Withdrawn successfully" << std::endl;
  sqlite3_finalize(stmt);
  return true;
}

bool SQLiteDatabaseInterface::deposit(const std::string &accNumber,
                                      double amount)
{
  std::string sql = "UPDATE accounts SET balance = balance + ? WHERE "
                    "acc_number = ?";

  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to deposit: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  sqlite3_bind_double(stmt, 1, amount);
  sqlite3_bind_text(stmt, 2, accNumber.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE)
  {
    std::cerr << "Failed to deposit!" << std::endl;
    sqlite3_finalize(stmt);
    return false;
  }

  std::cout << "Deposited successfully" << std::endl;
  sqlite3_finalize(stmt);
  return true;
}

bool SQLiteDatabaseInterface::transferMoney(const std::string &sourceAcc,
                                            const std::string &destAcc,
                                            double amount)
{
  bool status{true};
  status &= withdraw(sourceAcc, amount);
  status &= deposit(destAcc, amount);
  if (!status) return false;

  int srcUserId{}, destUserId{};
  getUserIdFromAccount(sourceAcc, srcUserId);
  getUserIdFromAccount(destAcc, destUserId);

  insertTransaction(srcUserId, TransactionType::WITHDRAW, amount, sourceAcc,
                    destAcc);
  insertTransaction(destUserId, TransactionType::DEPOSIT, amount, destAcc,
                    sourceAcc);
  return true;
}

bool SQLiteDatabaseInterface::insertTransaction(int userId,
                                                TransactionType type,
                                                double amount,
                                                const std::string &sourceAcc,
                                                const std::string &destAcc)
{
  std::string sql = "INSERT INTO transactions (user_id, type, amount, "
                    "source_acc, dest_acc, timestamp) VALUES (?, ?, ?, ?, ?, "
                    "datetime('now'))";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to insert transaction: " << sqlite3_errmsg(db)
              << std::endl;
    return false;
  }

  sqlite3_bind_int(stmt, 1, userId);
  sqlite3_bind_text(stmt, 2,
                    type == TransactionType::DEPOSIT ? "DEPOSIT" : "WITHDRAW",
                    -1, SQLITE_STATIC);
  sqlite3_bind_double(stmt, 3, amount);
  sqlite3_bind_text(stmt, 4, sourceAcc.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 5, destAcc.c_str(), -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE)
  {
    std::cerr << "Failed to insert transaction!" << std::endl;
    sqlite3_finalize(stmt);
    return false;
  }

  std::cout << "Transaction inserted successfully" << std::endl;
  sqlite3_finalize(stmt);
  return true;
}

bool SQLiteDatabaseInterface::getTransactionHistory(
    int userId, std::vector<TransactionData> &transactions)
{
  std::string sql = "SELECT id, type, amount, source_acc, dest_acc, timestamp "
                    "FROM transactions WHERE user_id = ?";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Failed to fetch transactions: " << sqlite3_errmsg(db)
              << std::endl;
    return false;
  }

  sqlite3_bind_int(stmt, 1, userId);

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
  {
    TransactionData transaction;
    transaction.id = sqlite3_column_int(stmt, 0);
    transaction.type = sqlite3_column_text(stmt, 1)[0] == 'D'
                           ? TransactionType::DEPOSIT
                           : TransactionType::WITHDRAW;
    transaction.amount = sqlite3_column_double(stmt, 2);
    transaction.sourceAcc =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
    transaction.destAcc =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
    transaction.timestamp =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
    transactions.push_back(transaction);
  }

  if (rc != SQLITE_DONE)
  {
    std::cerr << "Failed to fetch transactions!" << std::endl;
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);
  return true;
}

void SQLiteDatabaseInterface::disconnect(){
  if (db)
  {
    sqlite3_close(db);
    db = nullptr;
  }
}
