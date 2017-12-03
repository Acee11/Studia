#pragma once
#include <BalanceDecrementer.hpp>
#include <BalanceIncrementer.hpp>
#include <BankAccountClientView.hpp>


class BankAccount : public BalanceIncrementer, public BalanceDecrementer, public BankAccountClientView
{
public:
    virtual void decrementBalance(int);
    virtual void incrementBalance(int);
    virtual int getBalance() const;

private:
    int balance{};
};