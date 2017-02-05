mirror(leaf,leaf) :- !.
mirror(node(X,V,Y), node(Y1,V,X1)) :-
	mirror(X,X1),
	mirror(Y,Y1).

flatten(leaf,[]).
flatten(node(X,V,Y), Res) :-
	flatten(X,R1),
	append(R1,[V],T1),
	flatten(Y,R2),
	append(T1,R2,Res).