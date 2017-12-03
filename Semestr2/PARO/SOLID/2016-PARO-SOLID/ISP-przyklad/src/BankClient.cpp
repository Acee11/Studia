#include "BankClient.hpp"

#include <iostream>

void BankClient::use(std::shared_ptr<BankAccountClientView> clientView)
{
    using namespace std;
    cout << "Hello Client! Your balance is: " << clientView->getBalance() << " gp!\n";
    //account.incrementBalance(100);
    /* "Lol, Client has just hacked his account! */
}