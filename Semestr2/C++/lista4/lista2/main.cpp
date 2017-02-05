#include "rational.h"
#include "matrix.h"

using namespace std;

int main( int argc, char* argv [ ] )
{
    rational r1( 2, 6 );
    rational r2( 4, 3 );
    rational r3( 5,6 );
    rational r4( 1, 2 );

    cout << r1 + r2 << endl;
    cout << r2 * r3 << endl;
    cout << r3 / r4 << endl;
    cout << r4 - r1 << endl;



    matrix m1 = { { rational(1,2), rational(-2,7) }, { rational(1,3), rational(2,8) } };
    std::cout << m1 << "\n";

    matrix m2 = { { rational(-1,3),rational(2,5) }, { rational(2,7), rational(-1,7) } };
    std::cout << m2 << "\n";

    matrix m3 = { { 4,5}, { -1, 2 }};
    std::cout << m1 * m2 << '\n';
    std::cout << ((m1 * m2) * m3) - (m1 * (m2 * m3)) << '\n';
    //std::cout << (m1 * (m2 + m3)) - ((m1 * m2) + (m1 * m3)) << '\n';
    //std::cout << ((m1 + m2) * m3) - ((m1 * m3) + (m2 * m3)) << '\n';


    //std::cout << (m1.determinant() * m2.determinant()) - (m1 * m2).determinant() << '\n';
    //std::cout << (m1 * m1.inverse()) << '\n';
    //std::cout << m1. inverse( ) << "\n";
    //std::cout << m1. adjugate( ) << "\n";
    //std::cout << m2. inverse( ) << "\n";
}

