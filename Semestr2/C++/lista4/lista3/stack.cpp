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

double stack::operator[](size_t i) const
{
    if(i > size() - 1)
        throw std::runtime_error("");

    return tab[size() - 1 - i];
}

double& stack::operator[](size_t i)
{
    if(i > size() - 1)
        throw std::runtime_error("");

    return tab[size() - 1 - i];
}

void stack::operator += (double d)
{
    push(d);
}

void stack::operator += (const stack& s)
{
    ensure_capacity(size() + s.size());
    if(this == &s)
    {
        for(int i = size(); i < 2*size(); i++)
            tab[i] = tab[i - size()];
        current_size *= 2;
        return;
    }
    for(int i = s.size() - 1; i >= 0; --i)
        push(s[i]);
}

stack operator + (const stack& s1, const stack& s2)
{
    stack tmp = s1;
    tmp += s2;
    return tmp;
}
/*
stack stack::operator + (stack s)
{
    *this += s;
    return *this;
}
*/
std::ostream& operator << (std::ostream& stream, const stack& s)
{
	stream << "[ ";
	for(int i = 0; i < s.current_size; ++i)
		stream << s.tab[i] << " ";
	stream << "]";
	return stream;
}
