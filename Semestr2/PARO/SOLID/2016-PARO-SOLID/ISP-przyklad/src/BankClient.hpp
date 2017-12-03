#pragma once
#include <memory>
#include <BankAccountClientView.hpp>

class BankClient
{
public:
    void use(std::shared_ptr<BankAccountClientView> clientView);
};