#include <memory>

#include "Console.hpp"
#include "Handlers.hpp"

//#include "MyLittlePony.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Console console;

    console.addHandler(make_unique<Quitter>());
    console.addHandler(make_unique<Printer>());
    console.addHandler(make_unique<Sumator>());

    console.run();
    return 0;
}
