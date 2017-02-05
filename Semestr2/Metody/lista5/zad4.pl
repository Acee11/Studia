merge([], L, L) :- !.
merge(L, [], L) :- !.
merge([H1|T1], [H2|T2], [H1|Res]) :-
	H1 < H2,
	!,
	merge(T1, [H2|T2], Res).
merge([H1|T1], [H2|T2], [H2|Res]) :-
	merge([H1|T1], T2, Res).

mergesort([A],[A]) :- !.
mergesort(List,Res) :-
 halve(List, L1, L2),
 mergesort(L1, R1),
 mergesort(L2, R2),
 merge(R1, R2, Res).
