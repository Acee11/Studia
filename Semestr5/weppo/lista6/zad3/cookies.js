const express = require('express'),
    cookieParser = require('cookie-parser')

let app = express();
app.use(express.urlencoded({ extended: true }));
app.use(cookieParser('s3cr3t'))
app.set('view engine', 'ejs');
app.set('views', './views');

app.get('/', (req, res) => {
    res.cookie('cookie1', 'value1');
    res.cookie('signedcookie1', 'signedvalue1', {signed: true});
    res.end();
});

app.get('/viewcookies', (req, res) => {
    res.end(`cookie1: ${req.cookies.cookie1}\csingedcookie1: ${req.signedCookies.signedcookie1}`)
});

app.get('/unsetcookies', (req, res) => {
    res.cookie('cookie1', '', {maxAge: -1});
    res.cookie('signedcookie1', '', {maxAge: -1});
    res.end();

})

app.listen(3000)