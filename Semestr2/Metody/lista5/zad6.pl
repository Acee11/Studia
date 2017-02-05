init([],[]).
init([H|T],[[H]|R]) :-
	init(T,R).

merge_sort(L,R) :-
	init(L,L1),
	mergesortA(L1,R).



mergesortB([],[]).
mergesortB([H1],[H1]).
mergesortB([H1,H2|T],[HR|R]) :-
	merge(H1,H2, HR),
	mergesortB(T,R).

mergesortA([[H|T]],[H|T]) :- !.
mergesortA(List, Res) :-
	mergesortB(List, L1),
	mergesortA(L1,Res).