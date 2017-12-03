let Foo = function(x) {
    this.x = x
}

Foo.prototype = (function() {
    function Qux() {
        return 'qux' + this.x
    }

    return {
        Bar: function() {
            return 'bar' + this.x + Qux.apply(this)
        }
    }
})()

let foo = new Foo(1)
console.log(foo.Bar())
// console.log(foo.Qux())