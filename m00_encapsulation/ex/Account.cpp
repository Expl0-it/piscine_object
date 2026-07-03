#include "Account.hpp"
#include <ostream>

Account::Account(int id) : m_id(id), m_value(0)
{
}

std::ostream &operator<<(std::ostream &p_os, const Account &p_account)
{
	p_os << "[" << p_account.m_id << "] - [" << p_account.m_value << "]";
	return (p_os);
}

const int &Account::getId() const
{
	return (m_id);
}

const int &Account::getValue() const
{
	return (m_value);
}
