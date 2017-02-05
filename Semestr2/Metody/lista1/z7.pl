%dom(wlasiciel, numer, kolor, zwierze, papierosy, trunek)
sasiaduje(X,Y):-
                X=1,Y=2;
		X=2,Y=3;
		X=3,Y=4;
		X=4,Y=5.
sasiaduje(X,Y):-
                sasiaduje(Y,X).
%2
dom(anglik, _, czerwony,_,_,_).
%3
dom(hiszpan,_,_,pies,_,_).
%4
dom(_,_, zielony,_,_,kawa).
%5
dom(ukrainiec,_,_,_,_,herbata).
%6
dom(_,X,zielony,_,_,_):-
             dom(_,Y,bialy,_,_,_),
	     sasiaduje(X,Y).

%7
dom(_,_,_,waz, winston,_).
%8
dom(_,_, zolty,_, kool,_).
%9
dom(_,3,_,_,_,mleko).
%10
dom(norweg,1,_,_,_,_).
%11
dom(_,X,_,_,cheterfild,_):-
              dom(_,Y,_,lis,_,_), sasiaduje(X,Y).
%12
dom(_,X,_,kon,_,_):-
	      dom(_,Y,_,_,kool,_), sasiaduje(X,Y).
%13
dom(_,_,_,_,lucky,sok).
%14
dom(japonczyk,_,_,_,kent,_).
%15
dom(norweg,X,_,_,_,_):-
               dom(_,Y,niebieski,_,_,_), sasiaduje(X,Y).

rozmieszczenie(X) :- X = dom(_,_,_,_,_,_).




kolor(czerwony).
kolor(zielony).
kolor(zolty).
kolor(niebieski).
kolor(bialy).

wlasciciel(anglik).
wlasciciel(hiszpan).
wlasciciel(japonczyk).
wlasciciel(norweg).
wlasciciel(ukrainiec).

zwierze(pies).
zwierze(waz).
zwierze(lis).
zwierze(kon).
zwierze(slon).

papierosy(kool).
papierosy(winston).
papierosy(cheasterfield).
papierosy(lucky_strikes).
papierosy(kent).

napoj(kawa).
napoj(herbata).
napoj(mleko).
napoj(sok).
napoj(wodka).

nr(1).
nr(2).
nr(3).
nr(4).
nr(5).

dom(A, B, C, D, E, F) :- 
	kolor(A), wlasciciel(B), zwierze(C), papierosy(D), napoj(E), nr(F).
