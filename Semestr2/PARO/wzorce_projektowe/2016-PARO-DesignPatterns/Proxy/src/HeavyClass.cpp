#include <iostream>
#include <HeavyClass.hpp>

    HeavyClass::~HeavyClass() 
    {
        std::cout << "Test::~Test()" << std::endl;
    }

    void HeavyClass::printMe()
    {

        std::cout << "my weight is: "<<sizeof(HeavyClass) << std::endl;
    }

