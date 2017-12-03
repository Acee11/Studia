function isDivisibleBy(a, n)
{
    return (a%n) === 0;
}

function* f(low, high)
{
    if(low < 0 || high < 0)
        throw RangeError("numbers below zero not allowed");
    if(low > high)
        return;
    for(let i = low; i <= high; ++i)
    {
        let iDigits = i.toString().split('').map(d => parseInt(d));
        let sum = iDigits.reduce(function(a, b){
            return a + b;
        })
        if(!isDivisibleBy(i, sum))
            continue;
    
        let isValid = true;
        
        for(let digit of iDigits)
        {
            if(digit === 0)
                continue;
            if(!isDivisibleBy(i, digit))
            {
                isValid = false;
                break;
            }
        }
        if(isValid)
            yield i;
    }
}


for (let i of f(1,10000))
    console.log(i);