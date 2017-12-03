#pragma once

#include <memory>
#include "BalanceIncrementer.hpp"

class IncomingPayment
{
public:
    IncomingPayment(int value): value(value) { }
    void apply(std::shared_ptr<BalanceIncrementer> balanceIncrementer) const;

private:
    int value;
};