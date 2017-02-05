len([],X,X):-!.
len([_|T],N,L) :-
	L1 is L+1,
	len(T,N,L1).
len(X,N) :-
	len(X,N,0).
