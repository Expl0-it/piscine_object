#pragma once

#include "Bank.hpp"
#include <iostream>
#include <vector>

class Bank::Account {
private:
  int m_id;
  int m_value;

  Account(int id);

public:
  const int &getId() const;
  const int &getValue() const;
};
