#include "Account.hpp"
#include "Bank.hpp"
#include <exception>

int main(void) {
  Bank bankA = Bank();
  std::cout << bankA << std::endl;

  bankA.addLiquidity(1e6);
  bankA.createAccount();
  try {
    bankA.depositToAccount(8, 10);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl << std::endl;
  }
  std::cout << bankA << std::endl;

  return 0;
}
