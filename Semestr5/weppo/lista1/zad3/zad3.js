function isPrime(n)
{
    if(n <= 1)
        return false;
    for(let i = 2; i*i <= n; ++i)
        if(n%i === 0)
            return false;
    return true;
}

function* getPrimes(low, high)
{
    if(low < 0 || high < 0)
        throw RangeError("numbers below zero not allowed");
    if(low > high)
        return;
    for(let i = low; i <= high; ++i)
        if(isPrime(i))
            yield i;
}

for(let p of getPrimes(0, 100))
    console.log(p);