#ifndef _STACK
#define _STACK 1
#include <iostream>
#include <initializer_list>
#include <stdexcept>
class stack
{
    size_t current_size;
    size_t current_capacity;
// size_t is an integer number >= 0. It should be used for
// sizes of objects, for indexing (because an index lies
// between 0 and the size of the object) and for hash values
// (because a hash value will be used for indexing.)
// size_t is guaranteed to be big enough for the memory
// of every computer, now and in the future.
// size_t is an alias. Hence you need to include something
// from standard library in order to have it.
    double* tab;
// class invariant is that tab is always
// allocated with a block with current_capacity.
// We ignore the fact that normally,
// elements between current_size and current_capacity
// are not initialized.
    void ensure_capacity( size_t c );
// Ensure that stack has capacity of at least c.
public:
stack();
stack(std::initializer_list<double> d);

stack(const stack &s);

~stack();
// So that you can write s = { 1,2,3 };
// You need d. size( ) and for( double d : s ) .....
    void operator = ( const stack& s );
// These are the essential methods.
// Later we will also encounter
// void operator = ( stack&& s ) and
// stack( stack&& s ).
    void push( double d );  // Use ensure_capacity, so that
// pushing is always possible, as
// long as memory is not full.
    void pop( );
// Remove one element from the stack. It’s OK to write
// code that crashes, as long as you write clearly what are
// your preconditions, so:
// PRECONDITION:  The stack is not empty.
    void reset( size_t s );
// Pops element until stack has size s.
// PRECONDITION: s <= current_size.
    double& top( );
    double top( ) const;
// The second one is used when stack was declared const.
// The first one allows assignment.
// Both have precondition that the stack is non-empty.
    size_t size( ) const
    {
        return current_size;
    }
    bool empty( ) const
    {
        return current_size == 0;
    }

    double operator [] (size_t i) const;

    double& operator [] (size_t i);

    void operator += (double d);

    void operator += (const stack& s);

    friend stack operator + (const stack& s1, const stack& s2);
    //stack operator + (stack s);

    friend std::ostream& operator << (std::ostream& stream, const stack& s);
};

#endif
