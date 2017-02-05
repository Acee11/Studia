halve(X, L, R) :-
	halve(X, X, L, R).

halve(X, [], [], X).
halve(X, [_], [], X).
halve([H1|T], [_,_|T1], [H1|L], R) :-
	halve(T, T1, L, R).

