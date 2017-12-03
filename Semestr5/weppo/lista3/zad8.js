function* fib() {
    let n0 = 0,
        n1 = 1
    yield n0
    yield n1
    while (true) {
        [n0, n1] = [n1, n0 + n1]
        yield n1
    }
}

function* take(it, top) {
    let i = 0
    for(let x of it) {
        if(i >= top)
            break
        yield x
        ++i
    }
}
// zwróć dokładnie 10 wartości z potencjalnie
// "nieskończonego" iteratora/generatora
for (let num of take(fib(), 10)) {
    console.log(num);
}