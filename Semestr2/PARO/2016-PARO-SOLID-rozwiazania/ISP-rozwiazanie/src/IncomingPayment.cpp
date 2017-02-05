#include "IncomingPayment.hpp"

#include <iostream>

void IncomingPayment::apply(BalanceIncrementer& incrementer) const
{
    using namespace std;
    cout << "Apply IncomingPayment to BankAccount with value of " << value << " gp!\n";
    incrementer.incrementBalance(value);
}
