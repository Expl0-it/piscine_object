#pragma once

#include <cstddef>
#include <iostream>
#include <map>
#include <vector>

class Bank {
private:
  int m_liquidity;
  class Account;
  std::map<int, Account *> m_acc_map;
  static size_t acc_id;

public:
  Bank();
  Bank(int liquidity);
  Bank(const Bank &);
  Bank &operator=(const Bank &);
  ~Bank();

  const int &getLiquidity() const;
  void setLiquidity(int);
  void updateLiquidity(int);

  friend std::ostream &operator<<(std::ostream &p_os,
                                  const Bank::Account &p_account);
  friend std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank);
};
