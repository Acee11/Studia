#include "rational.h"

// Complete these methods:

rational::rational( ) : num{0}, denum{1}
{}

rational::rational( int i ) : num{i}, denum{1}
{}

rational::rational( int n, int d ) : num{n}, denum{d}
{
	if (d == 0)
	{
		throw std::invalid_argument("Division by 0");
	}
	normalize();
}


int rational::gcd( int n1, int n2 )
{
    if (n1 == 0) return 1;
    if (n1 < 0) (n1 = -n1);
    if (n2 < 0) (n2 = -n2);
    while(n2)
    {
        if(n1 < n2)
        {
            int tmp = n1;
            n1 = n2;
            n2 = tmp;
        }
        int t = n1 % n2;
        n1 = n2;
        n2 = t;
    }
    return n1;
}

void rational::normalize()
{
    int div = gcd(this->num, this->denum);
    this->num /= div;
    this->denum /= div;
}

int rational::getNum()
{
	return num;
}

void rational::setNum(int val)
{
	num = val;
}

int rational::getDenum()
{
	return denum;
}

void rational::setDenum(int val)
{
	if(val == 0)
		throw std::runtime_error("");
	denum = val;
}


rational rational::operator - () const
{
    return rational(-num, denum);
}

rational rational::operator + (const rational& r) const
{
    return rational(num * r.denum + r.num * denum, denum * r.denum);
}

rational rational::operator - (const rational& r) const
{
    return rational(num * r.denum - r.num * denum, denum * r.denum);
}

rational rational::operator * ( const rational& r) const
{
    return rational(num * r.num, denum * r.denum);
}

rational rational::operator / ( const rational& r) const
{
    if (r.num == 0)
    {
        throw std::invalid_argument("Division by 0");
    }
    return rational(num * r.denum, denum * r.num);
}

bool rational::operator == (const rational& r) const
{
    return num * r.denum == denum * r.num;
}
bool rational::operator != (const rational& r) const
{
    return !(*this == r);
}

std::ostream& operator << ( std::ostream& stream, const rational& r)
{
    if (r.num == 0)
    {
        stream << 0;
        return stream;
    }
    if(r.denum == 1)
    {
        stream << r.num;
        return stream;
    }
    stream << r.num << "/" << r.denum;
    return stream;
}
