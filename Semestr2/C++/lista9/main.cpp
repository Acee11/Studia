#include "fifteen.h"
#include <iostream>

int main()
{
	fifteen f;
	fifteen f1({{4,3,2,1},{8,7,6,5},{12,11,10,9},{0,15,14,13}});

	std::cout << f1 << '\n';
	fifteen::position pos = fifteen::solvedposition(0);
	std::cout << pos.first << " " << pos.second << '\n';

	std::cout << "Hash test:   " << f.fifteen::hashvalue() << "  " << f1.hashvalue() << '\n'
	<< f.hashvalue() << " " << fifteen({{2,1,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}}).hashvalue() << '\n';

	std::cout << "Equality test:   " << f.equals(f1) << " " << f.equals({{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}}) << '\n';

	std::cout << "issolved test:   " << f.issolved() << '\n';

	#if 0
	std::cout << "Move test:   " << '\n';
	std::cout << f << '\n';
	f.makemove(move::up);
	std::cout << f << "distance: " << f.distance() << '\n';
	f.makemove(move::left);
	std::cout << f << "distance: " << f.distance() << '\n';
	f.makemove(move::left);
	std::cout << f << "distance: " << f.distance() << '\n';
	f.makemove(move::down);
	std::cout << f << "distance: " << f.distance() << '\n';
	f.makemove(move::right);
	std::cout << f << "distance: " << f.distance() << '\n';
	f.makemove(move::up);
	std::cout << f << "distance: " << f.distance() << '\n';
	f.makemove(move::right);
	std::cout << f << "distance: " << f.distance() << '\n';
	#endif





	return 0;
}

/*

*/