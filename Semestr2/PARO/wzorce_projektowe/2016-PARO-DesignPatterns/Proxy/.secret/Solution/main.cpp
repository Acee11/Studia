#include <iostream>

template<typename T>
class ManagedPointer
{
public:
    ManagedPointer(T* p) : ptr(p) {}

    ~ManagedPointer() { delete ptr; }

    T* operator->() const { return ptr; }

    T& operator*() const { return *ptr; }
private:
    T* ptr;
};

class Test
{
public:
    ~Test() { std::cout << "Test::~Test()" << std::endl; }
    void printMe(std::ostream& out)
    {
        out << "Test::printMe" << std::endl;
    }
};

void memoryLeak()
{
    ManagedPointer<Test> test = new Test;
    test->printMe(std::cout);
    (*test).printMe(std::cout);
}
int main()
{
    memoryLeak();
}
