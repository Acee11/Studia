#pragma once

#include "BalanceDecrementer.hpp"

class OutgoingPayment
{
public:
    OutgoingPayment(int value): value(value) { }
    void apply(BalanceDecrementer&) const;

private:
    int value;
};