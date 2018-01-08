const express = require('express')

let app = express()
app.set('view engine', 'ejs')
app.set('views', './views')
app.use(express.urlencoded({ extended: true }))

app.get('/view1', (req, res) => {
    let options = [
        { id: '1', name: '1', text: '1 text' },
        { id: '2', name: '2', text: '2 text' },
        { id: '3', name: '3', text: '3 text' },
        { id: '4', name: '4', text: '4 text' }
    ]
    res.render('view1', {
        options: options
    })
})

app.get('/view2', (req, res) => {
    res.render('view2')
})

app.listen(3000)
