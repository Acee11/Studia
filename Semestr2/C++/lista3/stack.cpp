#include "stack.h"

stack::stack() : current_capacity(1), current_size(0), tab(new double[1])
{}

stack::stack(std::initializer_list<double> d)
{
    current_size = current_capacity = d.size();
    tab = new double[current_size];
    size_t i = 0;
    for(double val : d)
    {
        tab[i] = val;
        ++i;
    }
}

stack::stack(const stack &s)
{

    current_size = s.current_size;
    current_capacity = s.current_capacity;
    tab = new double[current_size];
    for(size_t i = 0; i < current_size; ++i)
        tab[i] = s.tab[i];
}

stack::~stack()
{
    delete[] tab;
}

void stack::ensure_capacity( size_t c )
{
    if( current_capacity < c )
    {
// New capacity will be the greater of c and
// 2 * current_capacity.
        if( c < 2 * current_capacity )
            c = 2 * current_capacity;
        double* newtab = new double[ c ];
        for( size_t i = 0; i < current_size; ++i )
            newtab[i] = tab[i];
        current_capacity = c;
        delete[] tab;
        tab = newtab;
    }
}



void stack::operator = (const stack &s)
{
	if(this == &s) return;
	current_size = s.current_size;
	current_capacity = s.current_capacity;
	delete[] tab;
	tab = new double[current_size];
	for(size_t i = 0; i < current_size; ++i)
		tab[i] = s.tab[i];
}

void stack::push(double d)
{
	ensure_capacity(current_size + 1);
	tab[current_size] = d;
	current_size++;
}

void stack::pop()
{
	current_size--;
}

void stack::reset(size_t s)
{
	while(current_size > s)
		current_size--;
}

double& stack::top()
{
	return tab[current_size-1];
}

std::ostream& operator << (std::ostream& stream, const stack& s)
{
	stream << "[ ";
	for(int i = 0; i < s.current_size; ++i)
		stream << s.tab[i] << " ";
	stream << "]";
	return stream;
}