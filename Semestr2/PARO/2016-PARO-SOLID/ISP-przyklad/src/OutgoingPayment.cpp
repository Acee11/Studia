#include "OutgoingPayment.hpp"

#include <iostream>

void OutgoingPayment::apply(BankAccount& account) const
{
    using namespace std;
    cout << "Apply OutgoingPayment to BankAccount with value of " << value << " gp!\n";
    account.decrementBalance(value);
}