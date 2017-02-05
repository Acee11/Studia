# -*- encoding: utf8 -*-
from sets import Set

slowniki = [Set([]) for i in range(20)]

for i in open('slowa.txt'):
	i = unicode(i[:-1],'utf8')
	i = i.lower()
	if len(i)<20:
		slowniki[len(i)].add(i)

def ppn(s):
	mem = {}
	res = ""
	c = 1
	for i in s:
		if i not in mem:
			mem[i] = str(c)
			res += str(c) + '-'
			c+=1
		else:
			res += mem[i] + '-'
	res = res[:-1]
	return res
	
def mozliwosci(slowo):
	res = []
	p = ppn(slowo)
	for i in slowniki[len(slowo)]:
		if ppn(i) == p:
			res.append(i)
	return res
	
	
def polamSzyfr(szyfr):
	szyfr = szyfr.split(' ')
	m = []
	kolejnosc = []
	for i in szyfr:
		m.append(mozliwosci(i))
	tmp = list(m)
	for i in range(len(m)):
		max = 0
		for j in range(len(tmp)):
			if len(tmp[j]) > max:
				max = len(tmp[j])
				maxindex = j
		tmp[maxindex] = []
		kolejnosc.append(maxindex)
	kolejnosc.reverse()
	polam(m,kolejnosc,{},szyfr,0)
	
def polam(mozliwosci,kolejnosc,kodowanie,zdanie,k):
	for i in mozliwosci[kolejnosc[k]]:
		kod = dict(kodowanie)
		flag = True
		for j in range(len(zdanie[kolejnosc[k]])):
			if zdanie[kolejnosc[k]][j] not in kod:
				kod[zdanie[kolejnosc[k]][j]] = i[j]
			elif kod[zdanie[kolejnosc[k]][j]] != i[j]:
				flag = False
				break
		if flag:
			if k == len(mozliwosci) - 1:
				wypiszZdanie(zdanie,kod)
			else:
				polam(mozliwosci,kolejnosc,kod,zdanie,k+1)
		
def wypiszZdanie(zdanie,kod):
	res = ""
	for i in zdanie:
		for j in i:
			if j in kod:
				res += kod[j]
			else:
				res += j
		res += ' '
	print res
	
szyfr = ["" for i in range(19)]
szyfr[0] = unicode('fulfolfu ćtąśśótą tlźlźltą','utf8')
szyfr[1]  = unicode('udhufńfd ąuąuęąę yrrożdśś śdśsdtsć','utf8')
szyfr[2]  = unicode('uwuąpwuw uw dwnuąźhąuąa','utf8')
szyfr[3]  = unicode('źlieżyaoąibugąl gilżzeoeażpąmćep oąlbinżeueol ańażćaploćezgl','utf8')
szyfr[4]  = unicode('owoirłfcpił rtrłrłoz toptćordąńrh cflłdpasrhfrtkó','utf8')
szyfr[5]  = unicode('rlkgkrztrm kęłbfcęźbfrb lkąfmręcgclc kąźskscftśźb abńblktscrązctścoeb','utf8')
szyfr[6]  = unicode('pwmśąwćkcźąźśyź wśąucąśwuąij ópuyóuwuąćcź aćóyuąźrmśyźć pwmśhźśyźuyjig źyrźćyźóeżą','utf8')
szyfr[7]  = unicode('ajoaójaj yónólcóc eb gałnnag wóśówśówyt a fmajajat m ebwytkynóki','utf8')
szyfr[8]  = unicode('lnźś lskfź włhyłnchgnóśn leąż ónltnżgśeląkf mh ónpćkeóśn ąśs g mkśąśeląkfćd ćknąnćd','utf8')
szyfr[9]  = unicode('eą śęóęśjńfo ięiuąjśęjro ybsćńż łęn ę iżuofdąłląłg ń óńłćyąłg yńeąuerłg','utf8')
szyfr[10]  = unicode('teóźjdtdjdlażibśźd źrlswńs udćdpdśrźdźfa dbśóśfad źreókfaż źhedbgd','utf8')
szyfr[11]  = unicode('nlgwdg mgcumyćąlćiya l źuwbymyć iapąołwęlgźy ęoumaźy dgog iapoasmyćpęlć ąu uąęlgftumaiya','utf8')
szyfr[12]  = unicode('paweł rychlikowski ąońrloi ądpók b ąheućdsdbclockg rychlisa','utf8')
szyfr[13]  = unicode('zomfp ruodbętm śu yópjdćutbutw bózć yóźóś ypoókpżćśółż dpżad','utf8')
szyfr[14]  = unicode('wbr łtńąh ęńlmotsż nkbseyokboć eh źhaźkseams błoams dr łhużć łh yramźń','utf8')#
szyfr[15]  = unicode('gbóglżlcńbk lótj ężbko nkgaży mjubkyąęł jgjśj rubkdr ębżasł mjubżżj ułnsldńąłr tł jsdąłęlr ułżbg','utf8')
szyfr[16]  = unicode('ż bydlófuscnis diblibnse yulmrdlży żgpzyomżng pyęoy źelirpy żgdlófusi lgźpm rył nąmoś dfzgt jclż aykh ćerbu łńwsęi źóp','utf8')#
szyfr[17]  = unicode('śezółjndpgdl śdńjnpr łwźa nerłfó wenwżedtgczfgó śndug mdodfn żsź hóezyu hdjnezbm żoóżoęąud nezfdłói g śgóżod','utf8')
szyfr[18]  = unicode('hcsa hłzaldka żiaźdok ońgaźda st hmry wgchzm mńdołźay dóą ńgżtfdtb ź óżaodt źagwm źdeó rśthżdy za fdtsuóm żhieóda oawtśdwagzt','utf8')#
		
		
for i in range(18,19):
	print "Szyfr nr: ",i
	polamSzyfr(szyfr[i])
			