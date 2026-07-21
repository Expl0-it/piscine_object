#pragma once

#include <cstddef>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

class Bank {
private:
  class Account;

  static size_t acc_id;

  int m_liquidity;
  std::map<int, Account *> m_acc_map;

public:
  Bank();
  Bank(int liquidity);
  Bank(const Bank &);
  Bank &operator=(const Bank &);
  ~Bank();

  const int &getLiquidity() const;
  void setLiquidity(int);
  void addLiquidity(int);

  int createAccount();
  void closeAccount(int id);
  void depositToAccount(int id, int amount);
  void withdrawFromAccount(int id, int amount);

  void loanToAccount(int id, int loanAmount);

  const Account &operator[](size_t);

  friend std::ostream &operator<<(std::ostream &p_os,
                                  const Bank::Account &p_account);
  friend std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank);
};
