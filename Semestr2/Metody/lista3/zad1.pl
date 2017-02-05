permut([],[]).
permut(X,[H|T]) :-
	select(H,X,Y),
	permut(Y,T).