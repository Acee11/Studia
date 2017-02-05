 # coding=utf-8
 
from sets import Set
from time import *

cezaryc = 0
jadwigac = 0
sewerync = 0
karolinac = 0
wandac = 0
hipolitc = 0
anastazyc = 0
barwickic = 0
gajowiecc = 0
lulekc = 0



cezary = Set(["cezary","cezaremu","cezarego","czarek","czarkowi","czarkiem","czaruœ","czarusia","m³ody baryka"])
karolina = Set(["karolina","karolinie","karolinê","karolino","karoliny","karusia","karusi","szar³atowiczówa"])
jadwiga = Set(["barykowa","jadwiga","matka cezarego","pani baryka","jadwidze"])
seweryn = Set(["seweryn","pan baryka","stary baryka","sewerynowi","sewerynie"])
wanda = Set(["wanda","wandzie","wandy","wandê","wand¹","wando","okszyñska","okszyñskiej","wandzi","wandzia","wandziu"])
hipolit = Set(["hipolit","hipolitowi","hipolicie","hipolita","hipolitem","wielos³awski","wielos³awskiemu","wielos³awskim"])
anastazy = Set(["anastazy","anastazemu","anastazym","ksi¹dz","ksiêdziu"])
barwicki = Set(["barwicki","barwickiemu","barwickim","w³adys³aw","w³adys³awowi"])
gajowiec = Set(["gajowiec","gajowcowi","szymon","szymona","gajowca","szymonowi","szymonie",])
lulek = Set(["lulek","lulka","lulkowi","antoni","antoniemu","lulku"])

for wiersz in open('Przedwiosnie.txt'):
	wiersz = wiersz.split( )
	for i in wiersz:
		l = i.lower()
		if(l in cezary):
			cezaryc += 1
		elif(l in karolina):
			karolinac += 1
		elif(l in jadwiga):
			jadwigac += 1
		elif(l in seweryn):
			sewerync += 1
		elif(l in wanda):
			wandac += 1
		elif(l in hipolit):
			hipolitc += 1
		elif(l in anastazy):
			anastazyc += 1
		elif(l in barwicki):
			barwickic += 1
		elif(l in gajowiec):
			gajowiecc += 1
		elif(l in lulek):
			lulekc += 1
			
print "Cezary: ",cezaryc
print "Hipolit: ",hipolitc
print "Karolina: ",karolinac
print "Anastazy: ",anastazyc
print "Lulek: ",lulekc
print "Wanda: ",wandac
print "Gajowiec: ",gajowiecc
print "Seweryn: ",sewerync
print "Barwicki: ",barwickic
print "Jadwiga: ",jadwigac


