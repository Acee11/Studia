const http = require('http'),
    express = require('express'),
    multer = require('multer')

let app = express()
app.set('view engine', 'ejs')
app.set('views', './views')
app.use(express.urlencoded({ extended: true }))
    
const storage = multer.diskStorage({
    destination: './uploads/',
    filename: (req, file, callback) => {
        console.log(file)
        callback(
            null, 
            `${file.fieldname}-${Date.now()}-${file.originalname}`
        )
    }
})
const upload = multer({
    storage: storage
});

app.get('/', (req, res) => {
    res.render('index')
})

app.post('/', upload.single('myfile'), (req, res) => {
    res.redirect('/')
})
app.listen(3000)