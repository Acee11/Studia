#include <ThrowingFunction.hpp>
#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        throwingFunction();
    }
    catch(std::runtime_error)
    {
        std::cout << "exception caught!\n";
    }
    std::cout << "if you can't see a destructor of HeavyClass we have a memory leak!\n";

}
