insert([],E,[E]).

insert([H|T],E,Res) :-
	H >= E,
	!,
	Res = [E,H|T].
insert([H|T],E,Res) :-
	insert(T,E,X),
	Res = [H|X].

ins_sort([],[]).
ins_sort([H|T],Res) :-
	ins_sort(T,X),
	insert(X,H,Res).
	