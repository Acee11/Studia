function fib1() {
    let _n0 = 0,
        _n1 = 1,
        first = true
    return {
        next: function () {
            if(!first) {
                [_n0, _n1] = [_n1, _n0 + _n1]
            }
            first = false
            return {
                value: _n0,
                done: false
            }
        }
    }
}
function* fib2() {
    let n0 = 0,
        n1 = 1
    yield n0
    yield n1
    while (true) {
        [n0, n1] = [n1, n0 + n1]
        yield n1
    }
}

let i = 0
// var _it = fib1();
// for (var _result; _result = _it.next(), !_result.done && i < 100;) {
//     console.log(_result.value);
//     ++i
// }

for(let x of fib2()) {
    console.log(x)
    i++
    if(i > 100)
        break
}