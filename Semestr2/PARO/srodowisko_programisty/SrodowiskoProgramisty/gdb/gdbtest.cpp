// 1. Uruchomienie programu i ustawienie pułapki
//    - gdb --tui ./app
//    - help (aby uzyskać pomoc)
//    - wystartować aplikację 'start'
//    - ustawić pułakpę w linii 17 'break linenumber'
//    - kontynuować aplikację aż dojdzie do lini z pułapką 'continue'
//    - wylistować ustawione pułapki 'info break'
//
// 2. Załączyć watchpoint'a na a*b+c/d
//    - powtórzyć kroki z punktu 1, jednak ustawić watchpoint'a zamiast breakpoint'a za pomocą polecenia watch a*b+c/d
// 3. Załączyć zrzucanie core-dump'a 'ulimit -c unlimited' oraz przeanalizować go 'gdb APP COREFILE'
// 4. Podłączyć się do działającego procesu - gdb attach "pid"
// UWAGA - pamiętać o kompilacji aplikacji z flagą g3
// Opis poleceń GDB http://www.yolinux.com/TUTORIALS/GDB-Commands.html

#include <cstddef>
#include <iostream>

int main(int argc, char * argv[])
{
    int a = 0, b = 0, c = 0;
    int d = 1;
    int * pointer = nullptr;

    a = 1;

    for(size_t i = 1; i < 10; ++i)
    {
        d = i;
    }

    b = 34;
    c = d * 2;
    a = b = 0;

    std::cout << "Pointer value" << *pointer << std::endl;

    return (a*b*c*d)? 1: 0;
}
