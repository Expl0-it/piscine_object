#pragma once

#include "Account.hpp"
#include <vector>

class Bank
{
  private:
	int m_liquidity;
	std::vector<Account *> m_clientAccounts;

  public:
	Bank();

	const int &getLiquidity() const;

	friend std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank);
};
