#include "case_insensitive.h"
#include <iostream>

char tolow(char c)
{
	if(c >= 65 && c <= 90)
		c += 32;
	return c;
}


bool case_insensitive::operator( ) ( const std::string& s1, const std::string& s2 ) const
{
	auto it1 = s1.begin();
	auto it2 = s2.begin();
	while(it1 != s1.end() && it2 != s2.end())
	{
		if(*it1 == *it2)
		{
			it1++;
			it2++;
			continue;
		}
		if(tolow(*it1) < tolow(*it2))
			return true;
		return false;
	}
	return (it1 == s1.end() && it2 != s2.end());
}	

size_t case_insensitive_hash::operator ( ) (const std::string & s) const
{
	size_t hash = 5381;
	for(const auto& c : s)
		hash = ((hash << 5) + hash) + tolow(c);
	return hash;
}

bool case_insensitive_equality::operator( ) ( const std::string& s1, const std::string& s2 ) const
{
	auto it1 = s1.begin();
	auto it2 = s2.begin();	
	while(it1 != s1.end() && it2 != s2.end())
	{
		if(tolow(*it1) == tolow(*it2))
		{
			++it1;
			++it2;
			continue;
		}
		return false;
	}	
	return (it1 == s1.end() && it2 == s2.end());
}	
