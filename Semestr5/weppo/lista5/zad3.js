const http = require('http'),
    fs = require('fs')

const resHTML = `
<html>
<body>
<a href="/download">download</a>
</body>
</html> 
`

fname = './zad3.js'

http.createServer((req, res) => {
    if(req.url === '/') {
        res.statusCode = 200
        res.setHeader('Content-Type', 'text/html')
        res.write(resHTML)
        res.end()
    }
    else if(req.url = '/download') {
        res.statusCode = 200
        res.setHeader(
            'Content-Disposition', 
            `attachment; filename=${fname}`
        )
        fs.createReadStream(fname)
            .pipe(res)
    }
}).listen(3000);