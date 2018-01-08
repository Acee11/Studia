const express = require('express'),
    session = require('express-session'),
    FileStore = require('session-file-store')(session)

let app = express()
app.use(session({
    secret: 's3cr3t',
    store: new FileStore(),
    cookie: { maxAge: 60 * 1000 },
    resave: true,
    saveUninitialized: false
}))
app.use(express.urlencoded({ extended: true }))
app.set('view engine', 'ejs')
app.set('views', './views')

app.get('/', (req, res) => {
    res.render('csrfindex', {
        username: req.session.username
    })
})

app.post('/login', (req, res) => {
    if (req.body.username) {
        req.session.username = req.body.username
    }
    res.redirect('/')
})
app.post('/logout', (req, res) => {
    if(req.session.username) {
        req.session.destroy((err) => {
            if (err) {
                console.log("Error")
            } else {
                res.clearCookie('connect.sid')
                res.redirect('/')
            }
        })
    }
})


app.listen(3000)