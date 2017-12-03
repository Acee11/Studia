const fib = require('../lista1/zad5/zad5.js')

// let mem = [0, 1]
function fibMem(n) {
    if (n in fibMem.mem) {
        return fibMem.mem[n];
    }
    fibMem.mem[n] = fibMem(n-1) + fibMem(n-2)
    return fibMem.mem[n]
}
function fibRange(n) {
    ret = [0, 1]
    let [a, b] = [0, 1]
    for(let i = 0; i < n; ++i) {
        [a, b] = [b, a+b]
        ret.push(a)
    }
    return ret
}
fibMem.mem = [0, 1]

fib.testFib(100000, fibMem, 'fibMem(100000)')
console.time('fibRange(100000)')
fibRange(100000)
console.timeEnd('fibRange(100000)')
fib.testFib(100000, fib.fibIter, 'fibIter(100000)')