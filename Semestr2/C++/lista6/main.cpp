#include "vectortest.h"
#include "listtest.h"
#include <cstdio>
#include <ctime>
#include <chrono>

int main()
{
	//std::istream inp("plik");
    std::vector< std::string > vect;
	std::vector<std::string> v = vectortest::readfile(std::cin);
	std::cout << v;

	std::chrono::duration<double> sec;
	
	auto l1 = listtest::randomstrings(10000,1000);
	//std::list<std::string> l2(l1.begin(), l1.end()); 
	auto l2 = listtest::randomstrings(10000,1000);

	auto clock1 = std::chrono::system_clock::now();
	listtest::sort_assign(l2);
	sec = std::chrono::system_clock::now() - clock1;
	std::cout << "Lista sortowana uzywajac sort_assign: " << sec.count() << std::endl;

	auto clock2 = std::chrono::system_clock::now();
	listtest::sort_move(l1);
	sec = std::chrono::system_clock::now() - clock2;
	std::cout << "Lista sortowana uzywajac sort_move: " << sec.count() << std::endl;
	
	auto w1 = vectortest::randomstrings(10000,1000);
	auto w2 = vectortest::randomstrings(10000,1000);
	auto w3 = vectortest::randomstrings(10000,1000);

	//std::vector<std::string> w2(l1.begin(), l1.end());
	//std::vector<std::string> w3(l1.begin(), l1.end());
	
	auto clock3 = std::chrono::system_clock::now();
	vectortest::sort_assign(w1);
	sec = std::chrono::system_clock::now() - clock3;
	std::cout << "Wektor sortowany uzywajac sort_assign: " << sec.count() << std::endl;

	auto clock4 = std::chrono::system_clock::now();
	vectortest::sort_move(w2);
	sec = std::chrono::system_clock::now() - clock4;
	std::cout << "Wektor sortowany uzywajac sort_move: " << sec.count() << std::endl;

	auto clock5 = std::chrono::system_clock::now();
	vectortest::sort_std(w3);
	sec = std::chrono::system_clock::now() - clock5;
	std::cout << "Wektor sortowany uzywajac sort_std: " << sec.count() << std::endl;
	

	return 0;

}