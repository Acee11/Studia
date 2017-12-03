const fs = require('fs'),
    { promisify } = require('util')
const fname = process.argv[2]

// sposob 1 (callback)

// fs.readFile(fname, (err, data) => {
//     console.log(data.toString())
// })


// // sposob 2 (promisify)
// const myReadFile = promisify(fs.readFile); 

// // po staremu
// myReadFile(fname)
// .then((data) => {
//     console.log(data.toString())
// })

// // po nowemu
// async function asyncReadFile(fname) {
//     const data = await myReadFile(fname)
//     console.log(data.toString())
// }
// asyncReadFile(fname)


// // sposob 3 

// function readFileAsync(fname) {
//     return new Promise((resolve, reject) => {
//         fs.readFile(fname, (err, data) => {
//             if(err) {
//                 reject(err)
//             }
//             resolve(data.toString())
//         })
//     })
// }

// readFileAsync(fname)
//     .then(console.log)
//     .catch(console.log)


