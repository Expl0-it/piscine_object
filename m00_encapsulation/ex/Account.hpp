#pragma once

#include "Bank.hpp"
#include <iostream>

class Bank::Account {
private:
  int m_id;
  int m_value;

  Account(int id);

  friend class Bank;

public:
  const int &getId() const;
  const int &getValue() const;
};
