insert(E, leaf, node(leaf, E, leaf)).
insert(E, node(L, E, R), node(L, E, R)).
insert(E, node(L, V, R), node(L1, V, R)) :-
	E < V,
	!,
	insert(E, L, L1).
insert(E, node(L, V, R), node(L, V, R1)) :-
	insert(E, R, R1).

find(E, node(_, E, _)) :- !.
find(E, node(L, V, _)) :-
	E < V,
	find(E, L).
find(E, node(_, _, R)) :-
	find(E, R).
findMax(E, node(_, E, leaf)) :- !.
findMax(E, node(_,_,R)) :-
	findMax(E, R).
delMax(leaf, leaf).
delMax(node(L,_,leaf), L) :- !.
delMax(node(L, V, R), node(L, V, R1)) :-
	delMax(R, R1).

delMin(node(leaf,V,R), V, R) :- !.
delMin(node(L, V, R), Val, node(L1,V,R)) :-
	delMin(L, Val, L1).



delete(_, leaf, leaf).
delete(V, node(leaf,V,leaf), leaf) :- !.
delete(V, node(L, V, leaf), L) :- !.
delete(V, node(leaf, V, R), R) :- !.
delete(V, node(L, V, R), node(L, Rmin, R1)) :-
	!,
	delMin(R, Rmin, R1).

delete(V, node(L,E,R),node(L1, E, R)) :-
	V < E,
	!,
	delete(V, L, L1). 

delete(V, node(L,E,R),node(L, E, R1)) :-
	delete(V, R, R1).

empty(leaf).

