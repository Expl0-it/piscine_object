#pragma once

#include <iostream>
#include <vector>

class Bank;

class Account
{
  private:
	int m_id;
	int m_value;

	Account(int id);

	friend class Bank;

  public:
	const int &getId() const;
	const int &getValue() const;
	friend std::ostream &operator<<(std::ostream &p_os, const Account &p_account);
};
