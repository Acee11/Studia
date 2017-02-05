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


static int gcd( int n1, int n2 )
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
	denum = val;
}


rational rational::operator - (const rational& r1)
{
    return rational(-r1.num, r1.denum);
}

rational rational::operator + (const rational& r1, const rational& r2)
{
    return rational(r1.num * r2.denum + r2.num * r1.denum, r1.denum * r2.denum);
}

rational rational::operator - (const rational& r1, const rational& r2)
{
    return rational(r1.num * r2.denum - r2.num * r1.denum, r1.denum * r2.denum);
}

rational rational::operator * ( const rational& r1, const rational& r2)
{
    return rational(r1.num * r2.num, r1.denum * r2.denum);
}

rational rational::operator / ( const rational& r1, const rational& r2)
{
    if (r2.num == 0)
    {
        throw std::invalid_argument("Division by 0");
    }
    return rational(nr1.um * r2.denum, r1.denum * r2.num);
}

bool rational::operator == ( const rational& r1, const rational& r2)
{
    return r1.num * r2.denum == r1.denum * r2.num;
}
bool rational::operator != ( const rational& r1, const rational& r2)
{
    return !(r1 == r2);
}

std::ostream& rational::operator << ( std::ostream& stream, const rational& r1)
{
    if (r1.num == 0)
    {
        stream << 0;
        return stream;
    }
    if(r1.denum == 1)
    {
        stream << r1.num;
        return stream;
    }
    stream << r1.num << "/" << r1.denum;
    return stream;
}
