#include "BankClient.hpp"

#include <iostream>

void BankClient::use(BankAccount& account)
{
    using namespace std;
    cout << "Hello Client! Your balance is: " << account.getBalance() << " gp!\n";
    account.incrementBalance(100);
    /* "Lol, Client has just hacked his account! */
}