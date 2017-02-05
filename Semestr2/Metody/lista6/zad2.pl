e(V1,V2,Edges) :-
	member((V1,V2), Edges).

path_dfs(V1, V2, Edges, Path) :-
	dfs(V2, [V1], [], Edges, Path).

dfs(_,[], _, _, _) :- !, fail.   %dfs(cel,kolekcja, odwiedzone, krawedzie, sciezka)
dfs(V, [V|_], _, _, [V]).
dfs(V1, Stack, Visited, Edges, Path) :-
	get_s(Stack, V2, NewStackv1),
	member(V2, Visited),
	!,
	dfs(V1, NewStackv1, Visited, Edges, Path).

dfs(V1, Stack, Visited, Edges, [V2|Path]) :-
	get_s(Stack, V2, NewStackv1),
	addAll_s(X, e(V2, X, Edges), NewStackv1, NewStackv2),
	dfs(V1, NewStackv2, [V2|Visited], Edges, Path).

