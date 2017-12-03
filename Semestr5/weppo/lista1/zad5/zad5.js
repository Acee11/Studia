exports.fibRec = fibRec
exports.fibIter = fibIter
exports.testFib = testFib

function fibRec(n)
{
    if(n <= 0)
        return 0;
    if(n === 1)
        return 1;
    return fibRec(n-1) + fibRec(n-2);
}

function fibIter(n)
{
    if(n <= 0)
        return 0;
    let n0 = 0;
    let n1 = 1;
    for(let i = 1; i < n; ++i)
    {
        let tmp = n1;
        n1 = n0 + n1;
        n0 = tmp;
    }
    return n1;
}

function testFib(n, fibFunc, timeStr="fibTime")
{
    console.time(timeStr);
    for(let i = 0; i < n; ++i)
        fibFunc(i);
    console.timeEnd(timeStr);
}
