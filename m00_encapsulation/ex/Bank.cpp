#include "Bank.hpp"

Bank::Bank() : m_liquidity(0)
{
}

std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank)
{
	p_os << "Bank informations : " << std::endl;
	p_os << "Liquidity : " << p_bank.getLiquidity() << std::endl;
	for (std::vector<Bank::Account *>::const_iterator it = p_bank.m_clientAccounts.begin();
	     it != p_bank.m_clientAccounts.end(); ++it)
	{
		Bank::Account *const &clientAccount = *it;
		p_os << *clientAccount << std::endl;
	}
	return (p_os);
}
