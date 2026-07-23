#include "Account.hpp"
#include "Bank.hpp"
#include <exception>
#include <iostream>

int main(void) {
  try {
    Bank bankA = Bank();
    std::cout << bankA << std::endl;

    bankA.setLiquidity(1e5);
    bankA.addLiquidity(42);
    std::cout << bankA.getLiquidity() << std::endl;

    bankA.createAccount();
    try {
      bankA.depositToAccount(8, 200);
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl << std::endl;
    }
    try {
      bankA.depositToAccount(0, -1);
    } catch (std::exception &e) {
      std::cerr << e.what() << std::endl << std::endl;
    }
    bankA.depositToAccount(0, 200);
    std::cout << bankA << std::endl;
    std::cout << bankA[0] << std::endl;
    try {
      bankA.closeAccount(0);
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl << std::endl;
    }
    bankA.withdrawFromAccount(0, 190);
    bankA.closeAccount(0);
    std::cout << bankA << std::endl;
    bankA.createAccount();
    bankA.depositToAccount(bankA.createAccount(), 100);
    std::cout << bankA << std::endl;
    bankA.loanToAccount(2, 100);
    std::cout << bankA << std::endl;
    try {
      bankA.loanToAccount(2, 1e7);
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl << std::endl;
    }
    bankA.payLoanBack(2, 50);
    std::cout << bankA[2] << std::endl;
    bankA.payLoanBack(2, 50);
    try {
      bankA.payLoanBack(2, 1e4);
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl << std::endl;
    }
    std::cout << bankA << std::endl;

    Bank bankB = Bank(1000);
    Bank bankC = bankA;
    Bank bankD = Bank(bankA);

    std::cout << bankB << std::endl;
    std::cout << bankC << std::endl;
    std::cout << bankD << std::endl;

    for (int i = 0; i < 100; i++) {
      bankA.createAccount();
      bankB.createAccount();
    }
    for (int i = 10; i < 50; i += 2) {
      bankB.closeAccount(i);
    }
    std::cout << "OK" << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl << std::endl;
  }
  return 0;
}
