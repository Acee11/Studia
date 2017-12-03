function sum(...args) {
    let s = 0
    for(let arg of args) {
        s += arg
    }
    return s
}
console.log(sum())
console.log(sum(1,2,3))
console.log(sum(1,2,3,4))
console.log(sum(1,2,3,4,5))