#include "IncomingPayment.hpp"

#include <iostream>

void IncomingPayment::apply(std::shared_ptr<BalanceIncrementer> balanceIncrementer) const
{
    using namespace std;
    cout << "Apply IncomingPayment to BankAccount with value of " << value << " gp!\n";
    balanceIncrementer->incrementBalance(value);
}
