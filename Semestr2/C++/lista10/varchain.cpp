
#include "varchain.h"
#include <algorithm>


std::ostream& operator << ( std::ostream& out, const powvar & p )
{
   if( p.n == 0 )
   {
      out << "1"; // Should not happen, but we still have to print something.
      return out;
   }

   out << p.v;
   if( p.n == 1 )
      return out;

   if( p.n > 0 )
      out << "^" << p.n;
   else
      out << "^{" << p.n << "}";
   return out;
}


std::ostream& operator << ( std::ostream& out, const varchain& c )
{
   if( c. isunit( ))
   {
      out << "1";
      return out;
   }

   for( auto p = c. repr. begin( ); p != c. repr. end( ); ++ p )
   {
      if( p != c. repr. begin( ))
         out << ".";
      out << *p;
   }

   return out;
}


int varchain::power( ) const 
{
   int p = 0;
   for( auto pv : repr )
      p += pv. n;
   return p;
}

void varchain::normalize()
{
	powvar_cmp comparator;
	std::sort(repr.begin(), repr.end(), comparator);
	std::vector <powvar> vect;
	for(const powvar& it : repr)
	{
		if (vect.empty())
			vect.push_back(it);
		else if (vect.back().v == it.v)
			vect.back().n += it.n;
		else
		{
			if(vect.back().n == 0)
				vect.pop_back();
			if(it.n == 0)
				continue;
			else
				vect.push_back(it);
		}
	}
	repr = vect;
}
/*
*/
int varchain::compare(const varchain& c1, const varchain& c2)
{
	powvar_cmp compare;
	auto it1 = c1.repr.begin();
	auto it2 = c2.repr.begin();
	while (it1 != c1.repr.end() && it2 != c2.repr.end())
	{
		if (it1->v < it2->v)
			return -1;
		else if (it1->v > it2->v)
			return 1;
		else
		{
			if (it1->n < it2->n)
				return -1;
			else if (it1->n > it2->n)
				return 1;
		}
		++it1;
		++it2;
	}
	if (it1 == c1.repr.end() && it2 == c2.repr.end())
		return 0;
	else if (it1 == c1.repr.end())
		return -1;
	else 
		return 1;
}

varchain operator * ( varchain c1, const varchain& c2 )
{
	varchain chain = c1;
	chain.repr.insert(chain.repr.end(), c2.repr.begin(), c2.repr.end());
	chain.normalize();
	return chain;
}

