const readline = require('readline')
const fs = require('fs')

const fname = process.argv[2]

const rl = readline.createInterface({
    input: fs.createReadStream(fname)
});

let summary = {}
rl.on('line', (line) => {
    addr = line.slice(0, line.indexOf(' - - '))
    summary[addr] = summary[addr]+1 || 1
})
rl.on('close', () => {
    for(let i of Object.keys(summary).sort((x, y) => summary[x]-summary[y]).reverse()) {
        console.log(`${i} ${summary[i]}`)
    }
})