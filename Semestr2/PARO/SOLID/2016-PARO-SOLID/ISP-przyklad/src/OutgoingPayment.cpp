#include "OutgoingPayment.hpp"

#include <iostream>

void OutgoingPayment::apply(std::shared_ptr<BalanceDecrementer> balanceDecrementer) const
{
    using namespace std;
    cout << "Apply OutgoingPayment to BankAccount with value of " << value << " gp!\n";
    balanceDecrementer->decrementBalance(value);
}