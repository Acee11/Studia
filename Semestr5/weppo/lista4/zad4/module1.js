const foo = require('./module2')
module.exports = bar

function bar(n) {
    if(n === 0) {
        return 0
    }
    return 1 + foo(n-1)
}