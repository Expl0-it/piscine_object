#include "Bank.hpp"
#include "Account.hpp"
#include <cstddef>
#include <cstdlib>
#include <map>
#include <stdexcept>
#include <utility>

size_t Bank::acc_id = 0;

// constructors / destructors

Bank::Bank() : m_liquidity(0) {}

Bank::Bank(int liquidity) : m_liquidity(liquidity) {}

Bank &Bank::operator=(const Bank &other) {
  if (this == &other)
    return (*this);

  for (std::map<size_t, Bank::Account *>::const_iterator it = m_acc_map.begin();
       it != m_acc_map.end(); it++) {
    delete it->second;
  }
  this->m_acc_map.clear();

  this->m_liquidity = other.m_liquidity;
  for (std::map<size_t, Bank::Account *>::const_iterator it =
           other.m_acc_map.begin();
       it != other.m_acc_map.end(); it++) {
    this->m_acc_map.insert(std::pair<int, Bank::Account *>(
        it->first, new Bank::Account(*(it->second))));
  }
  return (*this);
}

Bank::Bank(const Bank &other) { *this = other; }

Bank::~Bank() {
  for (std::map<size_t, Bank::Account *>::const_iterator it = m_acc_map.begin();
       it != m_acc_map.end(); it++) {
    if (it->second)
      delete it->second;
  }
  this->m_acc_map.clear();
}

// getters / setters

const int &Bank::getLiquidity() const { return (m_liquidity); }

void Bank::setLiquidity(int override) { m_liquidity = override; }

void Bank::addLiquidity(int toAdd) { m_liquidity += toAdd; }

// account management

// TODO: check all of this logic when i am feeling more alive than now
int Bank::createAccount() {
  this->m_acc_map.insert(
      std::pair<int, Bank::Account *>(acc_id, new Bank::Account(acc_id)));

  acc_id++;
  return (acc_id - 1);
}

void Bank::closeAccount(size_t id) {
  if (this->m_acc_map.at(id)->m_balance != 0)
    throw std::invalid_argument(
        "An account with balance different than zero cannot be closed.");
  if (this->m_acc_map.at(id))
    delete this->m_acc_map.at(id);
  this->m_acc_map.erase(id);
}

void Bank::depositToAccount(size_t id, int amount) {
  if (amount < 0)
    throw std::invalid_argument("Deposit amount cannot be lesser than zero.");

  int fee = 0.05 * amount;
  amount -= fee;
  this->m_liquidity += fee;
  this->m_acc_map.at(id)->m_balance += amount;
}

void Bank::withdrawFromAccount(size_t id, int amount) {
  if (amount < 0)
    throw std::invalid_argument(
        "Withdrawal amount cannot be lesser than zero.");
  if (amount > this->m_acc_map.at(id)->getBalance())
    throw std::invalid_argument(
        "Withdrawal amount cannot be greater than account's balance");
  this->m_acc_map.at(id)->m_balance -= amount;
}

// loan logic

void Bank::loanToAccount(size_t id, int amount) {
  if (amount < 0)
    throw std::invalid_argument("Loan amount cannot be lesser than zero.");
  if (amount > this->getLiquidity())
    throw std::invalid_argument(
        "Loan amount cannot be greater than the bank's liquidity");
  Bank::Account *acc = this->m_acc_map.at(id);
  this->m_liquidity -= amount;
  acc->m_debt += amount;
  acc->m_balance += amount;
}

void Bank::payLoanBack(size_t id, int amount) {
  if (amount < 0)
    throw std::invalid_argument("Payback amount cannot be lesser than zero.");
  Bank::Account *acc = this->m_acc_map.at(id);
  if (amount > acc->getDebt())
    throw std::invalid_argument(
        "Payback cannot be greater than account's debt");
  if (amount > acc->getBalance())
    throw std::invalid_argument(
        "Payback cannot be greater than account's balance");

  acc->m_debt -= amount;
  acc->m_balance -= amount;
  this->m_liquidity += amount;
}

// operator index access []

const Bank::Account &Bank::operator[](size_t id) const {
  return (*this->m_acc_map.at(id));
}

// ostream override

std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank) {
  p_os << "Bank informations : " << std::endl;
  p_os << "Liquidity : " << p_bank.getLiquidity() << std::endl;

  p_os << "Accounts: " << std::endl;
  for (std::map<size_t, Bank::Account *>::const_iterator it =
           p_bank.m_acc_map.begin();
       it != p_bank.m_acc_map.end(); ++it) {
    p_os << *(it->second) << std::endl;
  }
  return (p_os);
}
