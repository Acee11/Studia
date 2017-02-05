
#include "listtest.h"

#include <random>
#include <chrono>
#include <algorithm>

std::list<std::string> vect_to_list(const std::vector<std::string> &v)
{
	return std::list<std::string>(v.begin(), v.end());
}

void listtest::sort_move( std::list< std::string > & v )
{
	for(std::list< std::string >::iterator i = v.begin(); i != v.end(); ++i)
	{
		for(std::list< std::string >::iterator j = v.begin(); j != i; ++j)
				{
					if(*i > *j)
						std::swap(*i,*j);
				}
	}
}

void listtest::sort_assign(std::list<std::string> & v)
{
	for(std::list< std::string >::iterator i = v.begin(); i != v.end(); ++i)
	{
		for(std::list< std::string >::iterator j = v.begin(); j != i; ++j)
			{
				if(*i > *j)
				{
					std::string tmp = *i;
					*i = *j;
					*j = tmp; 
				}
			}
	}
}

std::list<std::string> listtest::randomstrings( size_t nr, size_t s )
{
	static std::default_random_engine gen( 
      std::chrono::system_clock::now( ). time_since_epoch( ). count( ) );
         // Narrowing long int into int, but that is no problem.

   	static std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012345689";
   	static std::uniform_int_distribution<int> distr( 0, alphabet. size( ) - 1);
      // More narrowing.

   	std::list< std::string > res;

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

std::ostream& 
operator << ( std::ostream& out, const std::list< std::string > & list)
{
	for(std::list<std::string>::const_iterator i = list.begin(); i != list.end(); ++i)
		out << *i << " ";
	return out;
}		




