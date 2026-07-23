#pragma once

#include <cstddef>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

class Bank {
private:
  class Account;

  size_t account_id;

  int m_liquidity;
  std::map<size_t, Bank::Account *> m_acc_map;

  void setLiquidity(int);
  void changeLiquidity(int);

  void accountChangeDebt(size_t, int);
  void accountChangeBalance(size_t, int);

public:
  Bank();
  Bank(int liquidity);
  Bank(const Bank &);
  Bank &operator=(const Bank &);
  ~Bank();

  const int &getLiquidity() const;

  size_t createAccount();
  void closeAccount(size_t id);
  void depositToAccount(size_t id, int amount);
  void withdrawFromAccount(size_t id, int amount);

  void loanToAccount(size_t id, int amount);
  void payLoanBack(size_t id, int amount);

  const Bank::Account &operator[](size_t) const;

  friend std::ostream &operator<<(std::ostream &p_os,
                                  const Bank::Account &p_account);
  friend std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank);
};
