let obj = {
    _y: null,
    get x() {
        return _y
    },
    set x(val) {
        _y = val
    },
    print: function() {
        console.log(_y)
    }
}

obj.x = 1234
obj.z = 4321
obj.print()
console.log(obj.z)

Object.defineProperty(obj, 'foo', {
    value: 2,
    // writable: true
    writable: false
})

p.x = 5;
p.setX(5);
p/heeloo();

console.log(obj.foo)
obj.foo = 3
console.log(obj.foo)