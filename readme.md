# 🏦 Bank of Terminal: Where Money Meets `Ctrl+C` 💸

Welcome to the **Bank of Terminal**—the only bank where your money is as virtual as your social life! 🌐💻  
*No suits, no queues, just you, your terminal, and questionable financial decisions.*

---

## 🚀 Features

- **Saving Accounts** 🐌: For when you want your money to grow slower than your coding skills.
- **Credit Accounts** 🔥: Spend money you don’t have! *(Disclaimer: We’re not responsible for your crippling debt.)*
- **Transactions** 💸: Move money between accounts like a hacker moving through firewalls.
- **CLI Magic** 🧙‍♂️: Navigate menus like you’re in a 90s text-based RPG. *“You are in a bank. There is a loan here.”*
- **SQLite Backend** 🗄️: Your data is stored so securely, even *we* don’t know where it is.

---

## ⚙️ Installation

1. **Clone this repo** (because stealing code is illegal, kids):
   ```bash
   git clone https://github.com/your-repo/bank-of-terminal.git
   cd bank-of-terminal
   ```
2. **Compile it** (you’ll need `g++` and SQLite):
   ```bash
   mkdir -p build
   cmake -G Ninja -B build -S .
   cmake --build ./build
   ```
   *If compilation fails, blame the developer. Or your life choices.*

3. **Run it** 🏃‍♂️💨:
   ```bash
   ./bank-of-terminal
   ```

---

## 🕹️ Usage

### Step 1: Launch the app.
### Step 2: Pretend you’re a bank robber hacking the mainframe.

#### Sample Commands:

**Add a user:**
```bash
> 2
Nickname: 🦸‍♂️ "Captain_C++"
Username: "i_heart_pointers"
Password: "password123" *(Classic.)*
```

**Create a savings account:**
```bash
> 2
Balance: 5000 *(Monopoly money accepted.)*
```

**Transfer money:**
```bash
> 4
Source: "S123" *(Your account)*  
Destination: "C456" *(Your cat’s account)*  
Amount: 1000 *(Because Mittens deserves it.)*
```

---

## 🧪 Testing Your “Fortune”

We included a very scientific test suite (aka `main.cpp`):

```cpp
// When you realize your code works:
void celebrate() {
  std::cout << "🎉💰";
  throw_money_into_the_void(); // Not implemented yet. PR welcome.
}
```

Run the tests to see if:
✅ You can add users (even if they’re just root and admin).  
✅ You can create accounts (spoiler: they start at $0).  
✅ You can lose money faster than crypto.  

---

## 🛠️ Contributing

Pull requests are welcome!  
(Bonus points if you:
- Add a feature called "ATM Interface" that just prints "HAHA NOPE".
- Fix my garbage code.
- Bribe me with pizza. 🍕)

### Become a contributor:
1. **Fork this repo.**
2. **Write code. Cry. Debug. Repeat.**
3. **Submit a PR.**
4. **Profit??? 💰**

---

## 📜 License

**MIT License**  
*Translation: Do whatever you want, but don’t sue me when your virtual bank gets hacked by a script kiddie.*

---

## 🙏 Acknowledgements

- **SQLite**: For pretending my database schema isn’t a crime against humanity.
- **C++**: For making me question my life choices.
- **You**: For reading this far. Go touch grass. 🌱

---

This README is guaranteed to be **37% more entertaining** than your average banking app documentation. 🚀  
*(Results may vary. No refunds.)*
