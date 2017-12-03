function forEach(a, f) {
    for(let elem of a) {
        f(elem)
    }
}

function map(a, f) {
    for(let i in a) {
        a[i] = f(a[i])
    }
    return a
}

function filter(a, f) {
    res = []
    for(let elem of a) {
        if(f(elem)) {
            res.push(elem)
        }
    }
    return res
}

var a = [1,2,3,4];
// forEach( a, _ => { console.log( _ ); } );
// [1,2,3,4]
// console.log(filter( a, _ => _ < 3 ))
// [1,2]
console.log(map( a, _ => _ * 2 ))
// [2,4,6,8]