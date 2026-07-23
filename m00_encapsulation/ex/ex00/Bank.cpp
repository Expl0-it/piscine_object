#include "Bank.hpp"
#include "Account.hpp"
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <map>
#include <stdexcept>
#include <utility>

// constructors / destructors

Bank::Bank() : account_id(0), m_liquidity(0) {}

Bank::Bank(int liquidity) : account_id(0), m_liquidity(liquidity) {}

Bank &Bank::operator=(const Bank &other) {
  if (this == &other)
    return (*this);

  for (std::map<size_t, Bank::Account *>::const_iterator it = m_acc_map.begin();
       it != m_acc_map.end(); it++) {
    delete it->second;
  }
  this->m_acc_map.clear();

  this->setLiquidity(other.m_liquidity);
  for (std::map<size_t, Bank::Account *>::const_iterator it =
           other.m_acc_map.begin();
       it != other.m_acc_map.end(); it++) {
    this->m_acc_map.insert(std::pair<size_t, Bank::Account *>(
        it->first, new Bank::Account(*(it->second))));
  }
  this->account_id = other.account_id;
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

void Bank::changeLiquidity(int toAdd) { m_liquidity += toAdd; }

// account management

void Bank::accountChangeDebt(size_t id, int amount) {
  this->m_acc_map.at(id)->m_debt += amount;
}

void Bank::accountChangeBalance(size_t id, int amount) {
  this->m_acc_map.at(id)->m_balance += amount;
}

// TODO: check all of this logic when i am feeling more alive than now
int Bank::createAccount() {
  this->m_acc_map.insert(std::pair<size_t, Bank::Account *>(
      account_id, new Bank::Account(account_id)));

  account_id++;
  return (account_id - 1);
}

void Bank::closeAccount(size_t id) {
  if (this->m_acc_map.at(id)->m_balance != 0)
    throw std::invalid_argument(
        "An account with balance different than zero cannot be closed.");
  if (this->m_acc_map.at(id)->m_debt != 0)
    throw std::invalid_argument(
        "An account with debt different than zero cannot be closed");
  if (this->m_acc_map.at(id))
    delete this->m_acc_map.at(id);
  this->m_acc_map.erase(id);
}

void Bank::depositToAccount(size_t id, int amount) {
  if (amount < 0)
    throw std::invalid_argument("Deposit amount cannot be lesser than zero.");

  int fee = 0.05 * amount;
  amount -= fee;
  this->changeLiquidity(fee);
  this->accountChangeBalance(id, amount);
}

void Bank::withdrawFromAccount(size_t id, int amount) {
  if (amount < 0)
    throw std::invalid_argument(
        "Withdrawal amount cannot be lesser than zero.");
  if (amount > this->m_acc_map.at(id)->getBalance())
    throw std::invalid_argument(
        "Withdrawal amount cannot be greater than account's balance");
  this->accountChangeBalance(id, amount);
}

// loan logic

void Bank::loanToAccount(size_t id, int amount) {
  if (amount < 0)
    throw std::invalid_argument("Loan amount cannot be lesser than zero.");
  if (amount > this->getLiquidity())
    throw std::invalid_argument(
        "Loan amount cannot be greater than the bank's liquidity");
  this->changeLiquidity(-amount);
  this->accountChangeDebt(id, amount);
  this->depositToAccount(id, amount);
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

  this->accountChangeDebt(id, -amount);
  this->accountChangeBalance(id, -amount);
  this->changeLiquidity(amount);
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
