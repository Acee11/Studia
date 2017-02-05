#ifndef SURFACE_INCLUDED
#define SURFACE_INCLUDED
#include "surf.h"
#include <vector>

struct surface
{
	surf* ref;
	surface( const surface& s )
		: ref(s.ref->clone()) { }
	surface( surface&& s )
		: ref(s.ref->clone()) { }
	surface( const surf& s )
		: ref(s.clone()) { }
	surface( surf&& s )
		: ref(s.clone()) { }
	void operator = ( const surface& s );
	void operator = ( surface&& s );
	void operator = ( const surf& s );
	void operator = ( surf&& s );
	~surface( )
	{
		delete ref;
	}
	const surf& getsurf( ) const { return *ref; }
// There is no non-const access, because
// changing would be dangerous.
};

std::ostream& operator << ( std::ostream& stream, const surface& s );

std::ostream& operator << ( std::ostream& stream,
const std::vector< surface > & table );

void print_statistics( const std::vector< surface > & table );

#endif