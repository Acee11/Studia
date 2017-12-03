#include "BankAccount.hpp"

int BankAccount::getBalance() const
{
    return balance;
}

void BankAccount::decrementBalance(int decrementBy)
{
    balance -= decrementBy;
}

void BankAccount::incrementBalance(int incrementBy)
{
    balance += incrementBy;
}
