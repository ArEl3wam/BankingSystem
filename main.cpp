#include "cli_manager.h"
#include "cli_state.h"
#include "database_interface.h"
#include "singleton.h"
#include <iostream>

void runDatabaseTests() {
  auto& db = Singleton<SQLiteDatabaseInterface>::getInstance();

  // Test 1: Add a new user
  int userId = -1;
  bool success = db.addUser("TestNick", "testuser", "testpass", userId);
  
  if(success && userId != -1) {
    std::cout << "✅ User added successfully. ID: " << userId << "\n";
    
    // Test 2: Add account for the new user
    const std::string testAccNumber = "TEST123";
    if(db.addAccount(userId, testAccNumber, 1000)) {
      std::cout << "✅ Account added successfully\n";
      
      // Test 3: Verify account exists
      if(db.getAccount(userId, testAccNumber)) {
        std::cout << "✅ Account verification successful\n";
      } else {
        std::cerr << "❌ Account verification failed\n";
      }
    } else {
      std::cerr << "❌ Failed to add account\n";
    }
  } else {
    std::cerr << "❌ Failed to add user\n";
  }

  // Cleanup
}

int main() {
  // Run tests before CLI interface
  // runDatabaseTests();

  // Uncomment below to run CLI normally
  auto manager = std::make_shared<CliManager>();
  manager->transitionToState(std::make_shared<MainMenuState>(nullptr));
  while(true) {
    std::string input{};
    std::getline(std::cin, input);
    manager->handleInput(input);
  }
  
  return 0;
}