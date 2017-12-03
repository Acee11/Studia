const http = require('http')

const getHTML = `
<html>
<body>
<form method='POST'>
<input type='text' name='data1' /> 
<input type='text' name='data2' /> 
<input type='submit' value='Zapisz' />
</form>
</body>
</html> 
`

const postHTML = `
<html>
<body>

</body>
</html> 
`


http.createServer((req, res) => {
    var imie;

    if (req.method == 'GET') {
        res.write(getHTML);
        res.end()
    } else {
        var buf = '';
        req.on('data', data => {
            buf += data.toString();
        });
        req.on('end', () => {
            res.write('<html><body>\n')

            var postData =
                buf.split("&").map(s => s.split('='))
                    .reduce((o, [k, v]) => (o[k] = v, o), {});

            res.write('got data:\n')
            for(let i in postData) {
                res.write(decodeURIComponent(postData[i]))
            }

            res.write('</body></html>')
            res.end()
        });
    }

}).listen(3000);