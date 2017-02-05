#pragma once

#include "BankAccountClientView.hpp"
#include "BalanceDecrementer.hpp"
#include "BalanceIncrementer.hpp"

class BankAccount : public BankAccountClientView,
                    public BalanceDecrementer,
                    public BalanceIncrementer
{
public:
    void decrementBalance(int) override;
    void incrementBalance(int) override;
    int getBalance() const override;

private:
    int balance{};
};