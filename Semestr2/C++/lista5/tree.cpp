#include "tree.h"

void tree::operator = (const tree& t)
{
	if(this == &t)
		return;
	pntr->refcnt--;
	if(pntr->refcnt == 0)
		delete pntr;

	*this = tree(t);
}

tree::~tree()
{
	pntr->refcnt--;
	if(pntr->refcnt == 0)
		delete pntr;
}

std::string& tree::functor()
{
	ensure_not_shared();
	return pntr->f;
}

std::string tree::functor() const
{
	return pntr->f;
}

tree& tree::operator[] (size_t i)
{
	ensure_not_shared();
	return pntr->subtrees[i];
}

tree tree::operator [] (size_t i) const
{
	return pntr->subtrees[i];
}

size_t tree::nrsubtrees() const
{
	return pntr->subtrees.size();
}

void tree::ensure_not_shared()
{
	if(pntr->refcnt > 1)
	{
		pntr->refcnt--;
		pntr = new trnode(pntr->f, pntr->subtrees, 1);
	}
}

std::ostream& operator << (std::ostream& stream, const tree& t)
{
	stream << "Root label: " << t.functor() << '\n' <<
			  "Number of Subtrees: " << t.nrsubtrees() << '\n' <<
			  "Refcnt: " << t.pntr->refcnt << '\n';
	for(int i = 0; i < t.nrsubtrees(); i++)
		stream << i << ".   " << t[i].functor() << "   " << t[i].pntr->refcnt <<  "\n";
	return stream;
}

tree subst (const tree& t, const std::string& var, const tree& val)
{
	if(t.nrsubtrees() == 0)
	{
		if(t.functor() == var)
		{
			return val;
		}
		return t;
	}
	
	tree res = t;
	for(int i = 0; i < t.nrsubtrees(); ++i)
		res.replaceSubtree(i, subst(t[i], var, val));
	return res;
}

size_t tree::getAddress() const
{
	return reinterpret_cast<size_t> (pntr);
}

void tree::replaceSubtree(size_t i, const tree& t)
{
	if(pntr -> subtrees[i].pntr != t.pntr)
	{
		ensure_not_shared();
		pntr->subtrees[i] = t;	
	}	
	
}
void tree::replaceFunctor(const std::string &f)
{
	if(pntr->f == f)
		return;
	ensure_not_shared();
	this->pntr->f = f;
}