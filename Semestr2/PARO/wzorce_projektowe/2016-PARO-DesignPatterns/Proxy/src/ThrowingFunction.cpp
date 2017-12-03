#include <ThrowingFunction.hpp>
#include <HeavyClass.hpp>
#include <stdexcept>

void throwingFunction()
{
    HeavyClass* aHeavyInstance = new HeavyClass;
    aHeavyInstance->printMe();
    (*aHeavyInstance).printMe();

    throw std::runtime_error("Some error");

    delete(aHeavyInstance);
}
