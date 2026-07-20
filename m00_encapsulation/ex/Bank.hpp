#pragma once

#include <iostream>
#include <vector>

class Bank {
private:
  int m_liquidity;
  class Account;
  std::vector<Account *> m_clientAccounts;

public:
  Bank();
  Bank(int liquidity);

  const int &getLiquidity() const;

  friend std::ostream &operator<<(std::ostream &p_os,
                                  const Bank::Account &p_account);
  friend std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank);
};
