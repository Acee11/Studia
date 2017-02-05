{-# OPTIONS_GHC -fno-warn-tabs #-}
module Slownie (Rodzaj(..), Waluta(..), slownie, toCurrency) where
import Data.List


data Rodzaj = Meski | Zenski | Nijaki deriving Show

data Waluta = Waluta {
	mianownik_poj :: String,
	mianownik_mn  :: String,
	dopelniacz_mn :: String,
	rodzaj        :: Rodzaj
} deriving Show

instance Eq Waluta where
    x == y = mianownik_poj x == mianownik_poj y


toCurrency :: String -> Waluta
toCurrency str = case str of
	"AUD" -> aud
	"BGN" -> bgn
	"BRL" -> brl
	"BYR" ->  byr
	"CAD" -> cad
	"CHF" -> chf
	"CNY" -> cny
	"CZK" -> czk
	"DKK" -> dkk
	"EUR" -> eur
	"GBP" -> gbp
	"HKD" -> hkd
	"HRK" -> hrk
	"HUF" -> huf
	"IDR" -> idr
	"ISK" -> isk
	"JPY" -> jpy
	"KRW" -> krw
	"MXN" -> mxn
	"MYR" -> myr
	"NOK" -> nok
	"NZD" -> nzd
	"PHP" -> php
	"PLN" -> pln
	"RON" -> ron
	"RUB" -> rub
	"SDR" -> sdr
	"SEK" -> sek
	"SGD" -> sgd
	"THB" -> thb
	"TRY" -> try
	"UAH" -> uah
	"USD" -> usd
	"ZAR" -> zar




aud = Waluta {
	mianownik_poj = "dolar australijski",
	mianownik_mn = "dolary australijskie",
	dopelniacz_mn = "dolarów australijskich",
	rodzaj = Meski
}

bgn = Waluta {
	mianownik_poj = "lew bułgarski",
	mianownik_mn = "lwy bułgarskie",
	dopelniacz_mn = "lwów bułgarskich",
	rodzaj = Meski
}

brl = Waluta {
	mianownik_poj = "real brazylijski",
	mianownik_mn = "reale brazylijskie",
	dopelniacz_mn = "reali brazylijskich",
	rodzaj = Meski
}

byr = Waluta {
	mianownik_poj = "rubel białoruski",
	mianownik_mn = "ruble białoruskie",
	dopelniacz_mn = "rubli białoruskich",
	rodzaj = Meski
}

cad = Waluta {
	mianownik_poj = "dolar kanadyjski",
	mianownik_mn = "dolary kanadyjskie",
	dopelniacz_mn = "dolarów kanadyjskich",
	rodzaj = Meski
}

chf = Waluta {
	mianownik_poj = "frank szwajcarski",
	mianownik_mn = "franki szwajcarskie",
	dopelniacz_mn = "franków szwajcarskich",
	rodzaj = Meski
}

cny = Waluta {
	mianownik_poj = "juan chiński",
	mianownik_mn = "juany chińskie",
	dopelniacz_mn = "juanów chińskich",
	rodzaj = Meski
}

czk = Waluta {
	mianownik_poj = "korona czeska",
	mianownik_mn = "korony czeskie",
	dopelniacz_mn = "koron czeskich",
	rodzaj = Zenski
}

dkk = Waluta {
	mianownik_poj = "korona duńska",
	mianownik_mn = "korony duńskie",
	dopelniacz_mn = "koron duńskich",
	rodzaj = Zenski
}

eur = Waluta {
	mianownik_poj = "euro",
	mianownik_mn = "euro",
	dopelniacz_mn = "euro",
	rodzaj = Nijaki
}

gbp = Waluta {
	mianownik_poj = "funt brytyjski",
	mianownik_mn = "funty brytyjskie",
	dopelniacz_mn = "funtów brytyjskich",
	rodzaj = Meski
}

hkd = Waluta {
	mianownik_poj = "dolar hongkoński",
	mianownik_mn = "dolary hongkońskie",
	dopelniacz_mn = "dolarów hongkońskich",
	rodzaj = Meski
}

hrk = Waluta {
	mianownik_poj = "kuna chorwacka",
	mianownik_mn = "kuny chorwackie",
	dopelniacz_mn = "kun chorwackich",
	rodzaj = Zenski
}

huf = Waluta {
	mianownik_poj = "forint węgierski",
	mianownik_mn = "forinty węgierski",
	dopelniacz_mn = "forintów węgierskich",
	rodzaj = Meski
}

idr = Waluta {
	mianownik_poj = "rupia indonezyjska",
	mianownik_mn = "rupie indonezyjskie",
	dopelniacz_mn = "rupii indonezyjskich",
	rodzaj = Zenski
}

isk = Waluta {
	mianownik_poj = "korona islandzka",
	mianownik_mn = "korony islandzkie",
	dopelniacz_mn = "koron islandzkich",
	rodzaj = Zenski
}

jpy = Waluta {
	mianownik_poj = "jen japoński",
	mianownik_mn = "jeny japońskie",
	dopelniacz_mn = "jenów japońskich",
	rodzaj = Meski
}

krw = Waluta {
	mianownik_poj = "won południowokoreański",
	mianownik_mn = "wony południowokoreańskie",
	dopelniacz_mn = "wonów południowokoreańskich",
	rodzaj = Meski
}

mxn = Waluta {
	mianownik_poj = "peso meksykańskie",
	mianownik_mn = "peso meksykańskie",
	dopelniacz_mn = "peso meksykańskich",
	rodzaj = Nijaki
}

myr = Waluta {
	mianownik_poj = "ringgit malezyjski",
	mianownik_mn = "ringgity malezyjskie",
	dopelniacz_mn = "ringgitow malezyjskich",
	rodzaj = Meski
}

nok = Waluta {
	mianownik_poj = "korona norweska",
	mianownik_mn = "korony norweskie",
	dopelniacz_mn = "koron norweskich",
	rodzaj = Zenski
}

nzd = Waluta {
	mianownik_poj = "dolar nowozelandzki",
	mianownik_mn = "dolary nowozelandzkie",
	dopelniacz_mn = "dolarów nowozelandzkich",
	rodzaj = Meski
}

php = Waluta {
	mianownik_poj = "peso filipińskie",
	mianownik_mn = "peso filipińskie",
	dopelniacz_mn = "peso filipińskich",
	rodzaj = Nijaki
}

pln = Waluta {
	mianownik_poj = "złoty",
	mianownik_mn = "złote",
	dopelniacz_mn = "złotych",
	rodzaj = Meski
}

ron = Waluta {
	mianownik_poj = "nowa leja rumuńska",
	mianownik_mn = "nowe leje rumuńskie",
	dopelniacz_mn = "nowych lei rumuńskich",
	rodzaj = Zenski
}

rub = Waluta {
	mianownik_poj = "rubel rosyjski",
	mianownik_mn = "ruble rosyjskie",
	dopelniacz_mn = "rubli rosyjskich",
	rodzaj = Meski
}

sdr = Waluta {
	mianownik_poj = "specjalne prawo ciągnienia",
	mianownik_mn = "specjalne prawa ciągnienia",
	dopelniacz_mn = "specjalnych praw ciągnienia",
	rodzaj = Nijaki
}

sek = Waluta {
	mianownik_poj = "korona szwedzka",
	mianownik_mn = "korony szwedzkie",
	dopelniacz_mn = "koron szwedzkich",
	rodzaj = Zenski
}

sgd = Waluta {
	mianownik_poj = "dolar singapurski",
	mianownik_mn = "dolary singapurskie",
	dopelniacz_mn = "dolarów singapurskich",
	rodzaj = Meski
}

thb = Waluta {
	mianownik_poj = "baht tajski",
	mianownik_mn = "bahty tajskie",
	dopelniacz_mn = "bahtów tajskich",
	rodzaj = Meski
}

try = Waluta {
	mianownik_poj = "lira turecka",
	mianownik_mn = "liry tureckie",
	dopelniacz_mn = "lir tureckich",
	rodzaj = Zenski
}

uah = Waluta {
	mianownik_poj = "hrywna",
	mianownik_mn = "hrywny",
	dopelniacz_mn = "hrywien",
	rodzaj = Zenski
}

usd = Waluta {
	mianownik_poj = "dolar amerykański",
	mianownik_mn = "dolary amerykańskie",
	dopelniacz_mn = "dolarów amerykańskich",
	rodzaj = Meski
}

zar = Waluta {
	mianownik_poj = "rand południowoafrykański",
	mianownik_mn = "randy południowoafrykańskie",
	dopelniacz_mn = "randów południowoafrykańskich",
	rodzaj = Meski
}

integerToTable :: Integer -> [Integer]
integerToTable x = reverse $ unfoldr f x where
	f 0 = Nothing
	f y = Just (y `mod` 1000, y `div` 1000)

convertTableToStr :: [Integer] -> Waluta -> String
convertTableToStr [] _ = ""
convertTableToStr [0] currency = dopelniacz_mn currency
convertTableToStr (x:xs) currency 
	| x == 0 = convertTableToStr xs currency
	| x == 1 = oneException len currency ++ " " ++ convertTableToStr xs currency 
	| otherwise = convertIntToStr x len currency ++ " " ++ convertTableToStr xs currency 
	where
		len = length (x:xs)

convertIntToStr :: Integer -> Int -> Waluta -> String
convertIntToStr num len currency 
	| num >= 100 = 
		hundredsNumberToStr (num `div` 100) ++ convertIntToStr (num `mod` 100) len currency 
	| num >= 20 = 
		tensNumberToStr (num `div` 10) ++ convertIntToStr (num `mod` 10) len currency
	| otherwise = 
		onesNumberToStr num (rodzaj currency) ++ getNumberName num len currency


oneException :: Int -> Waluta -> String
oneException 1 currency = case rodzaj currency of
	Meski -> "jeden " ++ mianownik_poj currency
	Zenski -> "jedna " ++ mianownik_poj currency
	Nijaki -> "jedno " ++ mianownik_poj currency
oneException 2 _ = "jeden tysiąc"
oneException k _ = "jeden " ++ getNumeral k 

onesNumberToStr :: Integer -> Rodzaj -> String
onesNumberToStr x kind = case x of
	0 -> ""
	1 -> case kind of
		Meski -> "jeden "
		Zenski -> "jedna "
		Nijaki -> "jeden "
	2 -> case kind of
		Meski -> "dwa "
		Zenski -> "dwie "
		Nijaki -> "dwa "
	3 -> "trzy "
	4 -> "cztery "
	5 -> "pięc "
	6 -> "sześc "
	7 -> "siedem "
	8 -> "osiem "
	9 -> "dziewięc "
	10 -> "dziesięc "
	11 -> "jedenaście "
	12 -> "dwanaście "
	13 -> "trzynaście "
	14 -> "czternaście "
	15 -> "piętnaście "
	16 -> "szesnaście "
	17 -> "siedemnaście "
	18 -> "osiemnaście "
	19 -> "dziewiętnaście "

-- assumption: x != 1 (onesNumberToStr manages this case)
tensNumberToStr :: Integer -> String
tensNumberToStr x = case x of
	0 -> ""
	2 -> "dwadzieścia "
	3 -> "trzydzieści "
	4 -> "czterdzieści "
	5 -> "pięćdziesiąt "
	6 -> "sześćdziesiąt "
	7 -> "siedemdziesiąt "
	8 -> "osiemdziesiąt "
	9 -> "dziewiećdziesiąt "

hundredsNumberToStr :: Integer -> String
hundredsNumberToStr x = case x of
	0 -> ""
	1 -> "sto "
	2 -> "dwieście "
	3 -> "trzysta "
	4 -> "czterysta "
	5 -> "piećset "
	6 -> "sześćset "
	7 -> "siedemset "
	8 -> "osiemset "
	9 -> "dziewięćset "

getNumberName :: Integer -> Int -> Waluta -> String
getNumberName num k currency
	| k == 1 = getCurrencyName num currency
	| k == 2 = getThousandName num
	| k > 2 = getNumeral k ++ getNumeralSuffix num

getCurrencyName :: Integer -> Waluta -> String
getCurrencyName num currency 
	| num >= 2 && num <= 4 = mianownik_mn currency
	| otherwise = dopelniacz_mn currency

--assumption: this function is used for numerals higher or equal to million
getNumeralSuffix :: Integer -> String
getNumeralSuffix x 
	| x >= 2 && x <= 4 = "y"
	| otherwise = "ów"

getThousandName :: Integer -> String
getThousandName num 
	| num >= 2 && num <= 4 = "tysiące"
	| otherwise = "tysięcy"

-- assumption: x >= 3
getNumeral :: Int -> String
getNumeral x
	| x < 20 = getBasicPrefix k ++ getNumberSuffix i
	| otherwise = getComplexPrefix k ++ getNumberSuffix i
	where 
		k = (x-1) `div` 2 
		i = (x-1) `mod` 2  

getBasicPrefix :: Int -> String
getBasicPrefix x = case x of
	1 -> "mi"
	2 -> "bi"
	3 -> "try"
	4 -> "kwadry"
	5 -> "kwinty"
	6 -> "seksty"
	7 -> "septy"
	8 -> "okty"
	9 -> "noni"

-- assumption: x < 1000
getComplexPrefix :: Int -> String
getComplexPrefix x = getComplexPrefixFirstPart a ++ getComplexPrefixSecondPart b ++ getComplexPrefixThirdPart c 
	where
		c = x `div` 100
		b = (x `mod` 100) `div` 10
		a = x `mod` 10

getComplexPrefixFirstPart :: Int -> String
getComplexPrefixFirstPart x
	| x == 0 = ""
	| x == 1 = "un"
	| x == 2 = "do"
	| x == 3 = "tri"
	| x == 4 = "kwatuor"
	| x == 5 = "kwin"
	| x == 6 = "seks"
	| x == 7 = "septen"
	| x == 8 = "okto"
	| x == 9 = "nowem"

getComplexPrefixSecondPart :: Int -> String
getComplexPrefixSecondPart x
	| x == 0 = ""
	| x == 1 = "decy"
	| x == 2 = "wicy"
	| x == 3 = "trycy"
	| x == 4 = "kwadragi"
	| x == 5 = "kwintagi"
	| x == 6 = "seksginty"
	| x == 7 = "septagi"
	| x == 8 = "oktagi"
	| x == 9 = "nonagi"

getComplexPrefixThirdPart :: Int -> String
getComplexPrefixThirdPart x
	| x == 0 = ""
	| x == 1 = "centy"
	| x == 2 = "ducenty"
	| x == 3 = "trycenty"
	| x == 4 = "kwadryge"
	| x == 5 = "kwinge"
	| x == 6 = "sescenty"
	| x == 7 = "septynge"
	| x == 8 = "oktynge"
	| x == 9 = "nonge"

getNumberSuffix :: Int -> String
getNumberSuffix 0 = "lion"
getNumberSuffix 1 = "liard"



slownie :: Waluta -> Integer -> String
slownie currency 0 = "zero " ++ dopelniacz_mn currency
slownie currency number
	| number >= (10^6000) = "mnóstwo"
	| number < 0 = "minus " ++ slownie currency (-number)
	| otherwise = convertTableToStr tab currency where
		tab = integerToTable number