bpolaczenie(wroclaw,warszawa).
bpolaczenie(wroclaw,krakow).
bpolaczenie(wroclaw,szczecin).
bpolaczenie(szczecin,lublin).
bpolaczenie(szczecin,gniezno).
bpolaczenie(warszawa,katowice).
bpolaczenie(gniezno,gliwice).
bpolaczenie(lublin,gliwice).

polaczenie(X,Y) :- bpolaczenie(X,Z), polaczenie(Z,Y).
polaczenie(X,Y) :- bpolaczenie(X,Y).


