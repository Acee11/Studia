#pragma once

#include "BankAccount.hpp"

class OutgoingPayment
{
public:
    OutgoingPayment(int value): value(value) { }
    void apply(BankAccount&) const;

private:
    int value;
};