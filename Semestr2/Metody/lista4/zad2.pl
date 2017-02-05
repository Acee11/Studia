connection(gliwice, wroclaw).
connection(wroclaw,warszawa).
connection(wroclaw, katowice).
connection(katowice, warszawa).


trip(M1, M2, X) :-
	X = [M1|T],
	trip(M1, M2, T, [M1]).

trip(M1, M2, [M2], _) :-
	connection(M1, M2).

trip(M1, M2, [H|T], V) :-
	connection(M1,H),
	\+ member(H,V),
	trip(H, M2, T, [H|V]).

