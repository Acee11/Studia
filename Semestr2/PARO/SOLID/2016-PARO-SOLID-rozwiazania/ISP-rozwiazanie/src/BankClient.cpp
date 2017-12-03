#include "BankClient.hpp"

#include <iostream>

void BankClient::use(BankAccountClientView& account)
{
    using namespace std;
    cout << "Hello Client! Your balance is: " << account.getBalance() << " gp!\n";
}