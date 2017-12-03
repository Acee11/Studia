#include "OutgoingPayment.hpp"

#include <iostream>

void OutgoingPayment::apply(BalanceDecrementer& decrementer) const
{
    using namespace std;
    cout << "Apply OutgoingPayment to BankAccount with value of " << value << " gp!\n";
    decrementer.decrementBalance(value);
}