#pragma once

#include "BankAccount.hpp"

class IncomingPayment
{
public:
    IncomingPayment(int value): value(value) { }
    void apply(BankAccount&) const;

private:
    int value;
};