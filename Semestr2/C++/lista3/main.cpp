#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
	stack s = {};
	//cout << s << endl;
	stack s1 = { 1, 2, 3, 4, 5 };
	stack s2 = s1; // Copy constructor.
	// j is not size_t, because multiplying size_t with itself is
	// unnatural:
	for( unsigned int j = 0; j < 20; ++ j )
		s2. push( j * j );
	//cout << s2 << endl;
	//cout << s1 << endl;
	s1 = s2;
	// Assignment.
	s1 = s1;
	// Always check for self assignment.
	s1 = { 100,101,102,103 };
	// Works because the compiler inserts constructor and
	// calls assignment with the result.
	//Won’t compile. In order to get it compiled, remove const
	#if 1
	stack& sconst = s1;
	cout << sconst << endl;
	sconst. top( ) = 20;
	sconst. push(15);
	cout << sconst << endl;
	#endif
	return 0;
}