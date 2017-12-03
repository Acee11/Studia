const fs = require('fs')

const fname = process.argv[2]

fs.readFile(fname, (err, data) => {
    if(err) {
        throw err
    }
    console.log(data.toString())
})