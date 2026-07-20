#include "Account.hpp"
#include <ostream>

Bank::Account::Account(int id) : m_id(id), m_value(0) {}

std::ostream &operator<<(std::ostream &p_os, const Bank::Account &p_account) {
  p_os << "[" << p_account.getId() << "] - [" << p_account.getValue() << "]";
  return (p_os);
}

const int &Bank::Account::getId() const { return (m_id); }

const int &Bank::Account::getValue() const { return (m_value); }
