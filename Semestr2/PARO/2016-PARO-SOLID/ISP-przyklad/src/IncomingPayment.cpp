#include "IncomingPayment.hpp"

#include <iostream>

void IncomingPayment::apply(BankAccount& account) const
{
    using namespace std;
    cout << "Apply IncomingPayment to BankAccount with value of " << value << " gp!\n";
    account.incrementBalance(value);
}
