flatten(L,R) :-
	flatten(L, R, []).

flatten([],R,R).
flatten([[] | T], R, Tail) :-
	!,
	flatten(T, R, Tail).
flatten([[H|T1] | T], Res, Tail) :-
	!,
	flatten(T, R1, Tail),
	flatten([H|T1], Res,R1).
flatten([H | T], [H|Res], Tail):-
	flatten(T, Res, Tail).










































































flatten2(L, Res) :-
	flatten2(L, Res, []).

flatten2([], Res, Res).
flatten2([[]|T], Res, Tail) :-
	!,
	flatten2(T, Res, Tail).
flatten2([ [H|T1] | T], Res, Tail) :-
	!,
	flatten2(T, R1, Tail),
	flatten2([H|T1], Res, R1).
flatten2([H|T], [H|Res], Tail) :-
	flatten2(T, Res, Tail).





