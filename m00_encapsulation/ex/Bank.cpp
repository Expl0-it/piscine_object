#include "Bank.hpp"
#include "Account.hpp"
#include <cstddef>
#include <map>
#include <utility>

size_t Bank::acc_id = 0;

Bank::Bank() : m_liquidity(0) {}

Bank::Bank(int liquidity) : m_liquidity(liquidity) {}

Bank &Bank::operator=(const Bank &other) {
  if (this == &other)
    return (*this);

  for (std::map<int, Bank::Account *>::const_iterator it = m_acc_map.begin();
       it != m_acc_map.end(); it++) {
    delete it->second;
  }
  this->m_acc_map.clear();

  this->m_liquidity = other.m_liquidity;
  for (std::map<int, Bank::Account *>::const_iterator it =
           other.m_acc_map.begin();
       it != other.m_acc_map.end(); it++) {
    this->m_acc_map.insert(
        std::pair<int, Account *>(it->first, new Account(*(it->second))));
  }
  return (*this);
}

Bank::Bank(const Bank &other) { *this = other; }

Bank::~Bank() {
  for (std::map<int, Bank::Account *>::const_iterator it = m_acc_map.begin();
       it != m_acc_map.end(); it++) {
    delete it->second;
  }
  this->m_acc_map.clear();
}

std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank) {
  p_os << "Bank informations : " << std::endl;
  p_os << "Liquidity : " << p_bank.getLiquidity() << std::endl;

  for (std::map<int, Bank::Account *>::const_iterator it =
           p_bank.m_acc_map.begin();
       it != p_bank.m_acc_map.end(); ++it) {
    p_os << *(it->second) << std::endl;
  }
  return (p_os);
}
