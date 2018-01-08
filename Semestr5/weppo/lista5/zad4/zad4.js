const http = require('http'),
    express = require('express'),
    Jimp = require('jimp'),
    util = require('util')

function WrongCouponFormatException() {}

Jimp.prototype.getBufferAsync = util.promisify(Jimp.prototype.getBuffer);
async function getCoupon(model) {
    try {
        if(!model.firstname || !model.lastname) {
            throw new WrongCouponFormatException()
        }
        let image = await Jimp.read(templateName)
        let font64 = await Jimp.loadFont(Jimp.FONT_SANS_64_BLACK)
        let font32 = await Jimp.loadFont(Jimp.FONT_SANS_32_BLACK)
        let name = `${model.firstname} ${model.lastname}`
        if(model.classname.length <= 7) {
            image.print(font64, 277, 16, model.classname)
        } else {
            image.print(font32, 287, 29, model.classname)
        }

        let originX = 216
        let originY = 215
        let deltaX = 85
        let sum = 0
        for(let i = 1; i <= 15; ++i) {
            let zad = model[`zad${i}`]
            if(zad === '') {
                zad = '0'
            }
            if(/^\d$/.test(zad)) {
                sum += parseInt(zad)
                image.print(font64, originX, originY, zad)
            } else {
                throw new WrongCouponFormatException()
            }

            originX += deltaX
        }

        image.print(font64, 1665, 219, sum.toString())
        image.print(font64, 1628, 120, model.date)

        image.print(font64, 882, 16, name)

        return image.getBufferAsync(image.getMIME())
    } catch(err) {
        throw err
    }

}
    
let app = express()
let templateName = './template.png'
    

app.set('view engine', 'ejs')
app.set('views', './views')



app.get('/', (req, res) => {
    model = {err: false}
    if(req.query.err) {
        model.err = true
    }
    res.statusCode = 200
    res.setHeader('Content-Type', 'text/html')
    res.render('./index', model)
})

app.use(express.urlencoded({ extended: true }))
app.use((req, res, next) => {
    res.setHeader('Content-Type', 'image/png')
    next()
})

app.get('/print', (req, res) => {
    (async function() {
        try {
            console.log(req.query)
            let coupon = await getCoupon(req.query)
            res.write(coupon)
            res.end()
        } catch(err) {
            if(err instanceof WrongCouponFormatException) {
                res.redirect('/?err=true')
            } else {
                console.log(err)
            }
        }
    })()
})

var server = http.createServer(app).listen(3000);