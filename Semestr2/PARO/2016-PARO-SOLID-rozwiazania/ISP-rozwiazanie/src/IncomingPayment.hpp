#pragma once

#include "BalanceIncrementer.hpp"

class IncomingPayment
{
public:
    IncomingPayment(int value): value(value) { }
    void apply(BalanceIncrementer&) const;

private:
    int value;
};