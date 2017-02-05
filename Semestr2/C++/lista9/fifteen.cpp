#include "fifteen.h"

fifteen::fifteen() 
: open_i(dimension-1), open_j(dimension-1)
{
	for(int i = 0; i < dimension; ++i)
		for(int j = 0; j < dimension; ++j)
			table[i][j] = dimension * i + j + 1;
	table[open_i][open_j] = 0;
}

fifteen::fifteen( std::initializer_list< std::initializer_list< size_t >> init )
{
	int ipos = 0;
	int jpos = 0;
	for(auto i = init.begin(); i != init.end() && ipos < dimension ; ++i)
	{
		for(auto j = (*i).begin(); j != (*i).end() ; ++j)
		{
			table[ipos][jpos] = *j;
			if (table[ipos][jpos] == 0)
			{
				open_i = ipos;
				open_j = jpos;
			}
			++jpos;
		}
		jpos = 0;
		++ipos;
	}
}

void fifteen::makemove( move m )
{
	switch(m)
	{
		case move::up:
			if(open_i == 0)
				throw illegalmove(m);
			std::swap(table[open_i][open_j],table[open_i-1][open_j]);
			--open_i;
			break;
		case move::down:
			if(open_i == dimension-1)
				throw illegalmove(m);
			std::swap(table[open_i][open_j],table[open_i+1][open_j]);
			++open_i;
			break;
		case move::left:
			if(open_j == 0)
				throw illegalmove(m);
			std::swap(table[open_i][open_j],table[open_i][open_j-1]);
			--open_j;
			break;
		case move::right:
			if(open_j == dimension-1)
				throw illegalmove(m);
			std::swap(table[open_i][open_j],table[open_i][open_j+1]);
			++open_j;
			break;
	}
}

size_t fifteen::hashvalue( ) const
{
	size_t hash = 5381;
	for(int i = 0; i < dimension; ++i)
		for(int j = 0; j < dimension; ++j)
			hash = ((hash << 5) + hash) + table[i][j];
	return hash;
}

bool fifteen::equals( const fifteen& other ) const
{
	for(int i = 0; i < dimension; ++i)
		for(int j = 0; j < dimension; ++j)
			if (table[i][j] != other.table[i][j])
				return false;
	return true;
}

bool fifteen::issolved( ) const
{
	for(int i = 0; i < dimension; ++i)
		for(int j = 0; j < dimension; ++j)
		{
			if(i == dimension-1 && j == dimension-1)
			{
				if(table[i][j] == 0)
					return true;
				else return false;
			}

			if (table[i][j] != i*dimension + j + 1)
				return false;
		}
	return true;
}

size_t fifteen::distance( ) const
{
	size_t sum = 0;
	for(int i = 0; i < dimension; ++i)
	{
		for(int j = 0; j < dimension; ++j)
		{
			auto pos = solvedposition(table[i][j]);
			sum += abs(i - pos.first) + abs(j - pos.second);
		}
	}
	return sum;
}

fifteen::position fifteen::solvedposition( size_t val )
{
	if (!val)
	{
		return fifteen::position(fifteen::dimension-1, fifteen::dimension-1);
	}
	return fifteen::position((val-1)/fifteen::dimension, (val-1) % fifteen::dimension);
}


std::ostream& operator << ( std::ostream& stream, const fifteen& f )
{
	for(int i = 0; i < f.dimension; ++i)
	{
		for(int j = 0; j < f.dimension; ++j)
			stream << std::setw(2) << f.table[i][j] << ' ';
		stream << '\n';
	}

	return stream;
}





