#pragma once

#include "Bank.hpp"
#include <cstddef>
#include <iostream>

class Bank::Account {
private:
  size_t m_id;
  int m_balance;
  int m_debt;

  Account(size_t id);

  friend class Bank;

public:
  const size_t &getId() const;
  const int &getBalance() const;
  const int &getDebt() const;
};
