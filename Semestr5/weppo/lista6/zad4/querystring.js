const express = require('express'),
    exec = require('child_process').exec,
    shellescape = require('shell-escape')

let app = express()
app.use(express.urlencoded({ extended: true }))
app.set('view engine', 'ejs')
app.set('views', './views')

app.get('/', (req, res) => {
    res.render('index')
})


app.get('/dictionary', (req, res) => {
    console.log(req.query)
    if (req.query.phrase) {
        // let phrase = shellescape([req.query.phrase])
        let phrase = req.query.phrase
        res.header("Content-Type", "text/plain; charset=utf-8");
        exec(`grep ${phrase} /usr/share/dict/american-english`, (err, stdout, stderr) => {
            res.end(stdout)
        })
    } else {
        res.redirect('/')
    }

})

app.listen(3000)