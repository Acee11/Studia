#pragma once

#include <memory>
#include "BalanceDecrementer.hpp"

class OutgoingPayment
{
public:
    OutgoingPayment(int value): value(value) { }
    void apply(std::shared_ptr<BalanceDecrementer> balanceDecrementer) const;

private:
    int value;
};