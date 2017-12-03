const bar = require('./module1')
module.exports = foo

function foo(n) {
    if(n === 0) {
        return 0
    }
    return 2 + bar(n-1)
}

