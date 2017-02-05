#include "grid.h"
#include <iterator>
#include <algorithm>

grid::grid( const grid& g )
   	: xsize(g.xsize), ysize(g.ysize), c(new cell [xsize * ysize])
{
	memcpy(c, g.c, xsize * ysize * sizeof(cell));
}

grid::grid( grid&& g)
	: xsize(g.xsize), 
	  ysize(g.ysize)
{
	std::swap(c, g.c);
}

void grid::operator = ( const grid& g )
{
	if(c == g.c)
		return;
	xsize = g.xsize;
	ysize = g.ysize;
	delete c;
	c = new cell[xsize * ysize];
	memcpy(c, g.c, xsize * ysize * sizeof(cell));
}
void grid::operator = ( grid&& g )
{
	xsize = g.xsize;
	ysize = g.ysize;
	std::swap(c, g.c);
}
grid::~grid( )
{
	delete c;
}

void grid::clear( )
{
	for(int y = 0; y < ysize; ++y)
		for(int x = 0; x < xsize; ++x)
			(*this)[x][y].s0 = (*this)[x][y].s0 = false;
}

void grid::plot() const
{
	for(int x = 0; x < xsize; ++x)
	{
		for(int y = 0; y < ysize; ++y)
		{
			if((*this)[x][y].s0)
			{
				int ix = -(xsize / 2) + x;
				int iy = -(ysize / 2) + y; 
				glBegin(GL_QUADS);
		      		glColor3f(1.0f, 0.5f, 0.2f); 
		      		glVertex2f(ix, iy);    
		      		glVertex2f(ix, iy + 1);
		      		glVertex2f(ix + 1, iy + 1);
		      		glVertex2f(ix + 1, iy + 0);
	   		 	glEnd();
	   		}
		}
	}
}

void grid::addfigure( unsigned int x, unsigned int y,
                   std::initializer_list< const char* > p )
{
	addfigure(x, y, figure(p));
}

void grid::addfigure( unsigned int x, unsigned int y, const figure& f )
{
	int fy = f.repr.size() - 1;
	for(int iy = y; iy < y + f.repr.size() && iy < ysize; ++iy)
	{
		int fx = 0;
		for(int ix = x; ix < x + f.repr[0].length() && ix < xsize; ++ix)
		{
			(*this)[ix][iy].s0 = isonchar(f.repr[fy][fx]);
			++fx;
		}
		--fy;
	}
	normalize();
}

unsigned int grid::cellsNearby(int x, int y, unsigned int s)
{
	unsigned int res = 0;
	for(int iy = y - 1; iy <= y + 1; ++iy)
	{
		if(iy < 0 || iy >= ysize)
			continue;
		for(int ix = x - 1; ix <= x + 1; ++ix)
		{
			if((ix == x && iy == y) || ix < 0 || ix >= xsize)
				continue;
			if(s == 1)
				res += (*this)[ix][iy].s1;
			else
				res += (*this)[ix][iy].s0;
		}
	}
	return res;
}

void grid::nextgeneration()
{
	grid res(xsize, ysize);
	for(unsigned int x = 0; x < xsize; ++x)
	{
		for(unsigned int y = 0; y < ysize; ++y)
		{
			res[x][y].s0 = (*this)[x][y].s1;
			
			bool cell = (*this)[x][y].s1;
			bool resCell = true;
			unsigned int nbCells = cellsNearby(x,y,1);
			if(cell == false)
			{
				if(nbCells == 3)
					resCell = true;
				else
					resCell = false;
			}
			else if(nbCells != 2 && nbCells != 3)
				resCell = false;

			res[x][y].s1 = resCell;
		}
	}
	*this = std::move(res);
}

void grid::normalize()
{
	for(int x = 0; x < xsize; ++x)
	{
		for(int y = 0; y < ysize; ++y)
		{
			bool resCell = true;
			bool cell = (*this)[x][y].s0;
			unsigned int nbCells = cellsNearby(x, y, 0);
			if(cell == false)
			{
				if(nbCells == 3)
					resCell = true;
				else
					resCell = false;
			}
			else if(nbCells < 2 || nbCells > 3)
				resCell = false;
			(*this)[x][y].s1 = resCell;
		}
	}
}

std::ostream& operator << ( std::ostream& stream, const grid& g)
{
	for(int y = g.ysize - 1; y >= 0; --y)
	{
		for(int x = 0; x < g.xsize; ++x)
		{
			if(g[x][y].s0)
				stream << "0";
			else
				stream << ".";
			if((x+1) % g.xsize != 0)
				stream << " ";
		}
		if(y != 0)
			stream << std::endl;
	}
	return stream;
}