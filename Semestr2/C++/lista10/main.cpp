
#include "varchain.h"
#include "polynomial.h"
#include "bigint.h"
#include "rational.h"


template< typename N >
polynomial< N > exptaylor( unsigned int n )
{
   varchain v;

   N fact = 1;

   polynomial< N > result;
   for( unsigned int i = 0; i < n; ++ i )
   {
      result[v] += fact;
      v = v * powvar( "x" );
      fact = fact / (i+1);
   }

   return result;
}

int main( int argc, char* argv [] )
{
   polynomial<int> pol;
   pol[{}] = 1;
   pol[{"x"}] = 2;

   polynomial<int> r = 1;
   for(int i = 0; i < 3; ++i)
      r = r * pol;
   std::cout << r << std::endl;
/*
   std::vector<powvar> vect;
   for(int i = 0; i < 5; i++)
        vect.push_back(powvar("x"));

   varchain chain(vect);
   varchain chain1({powvar("y",-5),powvar("y",-12), powvar("y",3), powvar("x",17)});

   std::cout << chain1 * chain << std::endl;
   polynomial< rational > pol;

   int N = 50;

   pol[ { } ] = 1;
   pol[ { "x" } ] = rational( 1, N ); 

   
   polynomial< rational > res = 1;
 
   for( int i = 0; i < N; ++i )
      res = res * pol;

   std::cout << "result = " << res << "\n";

   std::cout << " taylor expansion = " << exptaylor<rational>(20) << "\n";

   std::cout << "difference = " ;  
   std::cout << res - exptaylor<rational> ( 40 ) << "\n";
*/
   return 0;
}


