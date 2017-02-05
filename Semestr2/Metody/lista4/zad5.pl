flatten(leaf,[]).
flatten(node(X,V,Y), Res) :-
	flatten(X,R1),
	append(R1,[V],T1),
	flatten(Y,R2),
	append(T1,R2,Res).

insert(leaf,El,node(leaf,El,leaf)).

insert(node(X,Val,Y), El, Res) :-
	Val > El,
	!,
	Res = node(X1, Val, Y),
	insert(X, El, X1).

insert(node(X,Val,Y), El, Res) :-
	Res = node(X, Val, Y1),
	insert(Y, El, Y1).	

treesort(L,Res) :-
	treesort(L, leaf, Res).

treesort([], X, Res) :-
	flatten(X, Res).

treesort([H|T], X, Res) :-
	insert(X, H, Y),
	treesort(T,Y,Res).


