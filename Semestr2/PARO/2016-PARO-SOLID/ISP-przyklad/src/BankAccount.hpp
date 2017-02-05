#pragma once

class BankAccount
{
public:
    void decrementBalance(int);
    void incrementBalance(int);
    int getBalance() const;

private:
    int balance{};
};