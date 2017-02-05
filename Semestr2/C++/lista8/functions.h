#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER
#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>

template < typename C > 
std::map< std::string, unsigned int, C > frequencytable(
const std::vector< std::string > & text )
{
	std::map<std::string, unsigned int, C> map;
	for(const auto & str : text)
	{
		if(map.find(str) == map.end())
			map[str] = 1;
		else
			map[str]++;
	}
	return map;
}

template < typename C >
std::ostream& operator << ( std::ostream& out,
const std::map< std::string, unsigned int, C > & freq )
{
	for(const auto & it : freq)
		out << it.first << " : " << it.second << '\n';
	return out;
}

template<typename Hasher, typename Comparator>
std::unordered_map< std::string, unsigned int, Hasher, Comparator >
hashed_frequencytable( std::vector<std::string> text )
{
	std::unordered_map< std::string, unsigned int, Hasher, Comparator > map;
	for(const auto & str : text)
	{
		if(map.find(str) == map.end())
			map[str] = 1;
		else
			map[str]++;
	}
	return map;
}

template < typename Hasher, typename Comparator >
std::ostream& operator << ( std::ostream& out,
const std::unordered_map< std::string, unsigned int, Hasher, Comparator > & freq )
{
	for(const auto & it : freq)
		out << it.first << " : " << it.second << '\n';
	return out;
}





#endif
