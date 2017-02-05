#ifndef CASE_INSENSITIVE
#define CASE_INSENSITIVE
#include <string>

char tolow(char c);


struct case_insensitive
{
	bool operator( ) ( const std::string& s1, const std::string& s2 ) const;
};

struct case_insensitive_hash
{
	size_t operator ( ) (const std::string & s) const;
};

struct case_insensitive_equality
{
	bool operator ( ) (const std::string & s1, const std::string & s2) const;
};

#endif