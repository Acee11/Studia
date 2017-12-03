#include <iostream>

#include <memory>
#include "OutgoingPayment.hpp"
#include "IncomingPayment.hpp"
#include "BankAccount.hpp"
#include "BankClient.hpp"

using namespace std;

int main(int argc, char **argv)
{
    auto account = std::make_shared<BankAccount>();
    //BankAccount account;
    BankClient client;
    IncomingPayment incomingPayment{11};
    OutgoingPayment outgoingPayment{10};

    incomingPayment.apply(account);

    outgoingPayment.apply(account);

    client.use(account);
    client.use(account);
    client.use(account);
    client.use(account);

    return 0;
}
