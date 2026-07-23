#include "Account.hpp"
#include <cstddef>
#include <ostream>

Bank::Account::Account(size_t id) : m_id(id), m_balance(0), m_debt(0) {}

const size_t &Bank::Account::getId() const { return (m_id); }

const int &Bank::Account::getBalance() const { return (m_balance); }

const int &Bank::Account::getDebt() const { return (m_debt); }

std::ostream &operator<<(std::ostream &p_os, const Bank::Account &p_account) {
  p_os << "[ id: " << p_account.getId()
       << "] - [ balance: " << p_account.getBalance()
       << "] - [ debt: " << p_account.getDebt() << "]";
  return (p_os);
}
