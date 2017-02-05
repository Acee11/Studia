#include "functions.h"
#include "case_insensitive.h"
#include <iostream>
#include <string>
#include <set>
#include <random>
#include <chrono> 

std::vector< std::string > randomstrings( size_t nr, size_t s )
{
   static std::default_random_engine gen( 
      std::chrono::system_clock::now( ). time_since_epoch( ). count( ) );
         // Narrowing long int into int, but that is no problem.

   static std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012345689";
   static std::uniform_int_distribution<int> distr( 0, alphabet. size( ) - 1);
      // More narrowing.

   std::vector< std::string > res;

   for( size_t i = 0; i < nr; ++ i )
   {
      std::string rand;
      for( size_t j = 0; j < s; ++ j )
      {
         rand. push_back( alphabet[ distr( gen ) ] );  
      }

      res. push_back( std::move( rand ));
   }
   return res;
}

int main()
{
	std::vector<std::string> vect = {"aAa","bb","aaA","ccc", ""};

	//std::cout << frequencytable<case_insensitive>( std::vector< std::string >
	//{ "AA", "aA", "Aa", "this", "THIS" } );

	case_insensitive c;
	//std::cout << c( "a", "A" ) << c( "a","b" ) << c( "A", "c" ) << c( "a", "" ) << c( "", "" ) << "\n";

	case_insensitive_equality ce;
		std::cout << ce( "a", "A" ) << ce( "a","b" ) << ce( "A", "c" ) << "\n";

	case_insensitive_hash ch;

	auto map1 = frequencytable<case_insensitive>(vect);

	//std::cout << map1;

	auto map2 = hashed_frequencytable<case_insensitive_hash, case_insensitive_equality>(vect);	

	//std::cout << map2;
#if 0
	std::vector<std::string> randstr = randomstrings(100000, 30);
	std::set<std::string> set;
	for(auto &str : randstr)
	{
		if(set.find(str) == set.end())
			set.insert(str);
		else
			std::cout << str << '\n';
	}
#endif


	return 0;
}