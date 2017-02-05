revall([],[]).

revall([H|T],Res) :-
	H = [_|_],
	!,
	revall(H,R1),
	revall(T,R2),
	append(R2,[R1],Res).

revall([H|T],Res) :-
	revall(T,R2),
	append(R2,[H],Res).