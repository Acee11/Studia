function createGenerator(n) {
    return () => {
        var _state = 0;
        return {
            next: function () {
                return {
                    value: _state,
                    done: _state++ >= n
                }
            }
        }
    }
}

var foo = {
    [Symbol.iterator]: createGenerator(4)
};
var boo = {
    [Symbol.iterator]: createGenerator(22)
}
for (var f of foo)
    console.log(f);

for (var b of boo)
    console.log(b);