filter([],[]).
filter([H|T], [H|S]) :-     %Y - nieujemne elementy listy X
	H >= 0,
	filter(T,S).
filter([H|T],S) :-
	H < 0,
	filter(T,S).	

count(_,[],0).

count(E, [E|T], C) :-
	count(E, T, W),!,
	C is W+1.

count(E, [_|T], C) :-
	count(E,T,C).

exp(B, E, R) :-
	R is B^E.
