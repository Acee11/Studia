appn([],[]).
appn([ [] | T ], Res) :-
	appn(T, Res).
appn([ [H|T] |Tail], [H|Res]):-
	appn([T | Tail], Res).



appnv2(L, Res) :-
	appnv2(L, Res, []).

appnv2([], X, X).
appnv2([[H|T]],[H|Res], Tail) :-
	!,
	appnv2([T], Res, Tail).
appnv2([[]], X, X) :-
	!.
appnv2([H|T], Res, Tail) :-
	appnv2(T, R, Tail),
	appnv2([H], Res, R).