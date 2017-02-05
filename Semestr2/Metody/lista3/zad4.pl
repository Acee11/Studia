minimum([H],H).
minimum([H|T],Min) :-
	minimum(T,X),
	H =< X,
	Min = H,
	!.
minimum([_|T],Min) :-
	minimum(T,X),
	Min = X.


select_min(List, Min, Rest) :-
	minimum(List,Min),
	select(Min,List,Rest).

sel_sort([],[]).
sel_sort(List,Res) :-
	select_min(List,Min,Rest),
	Res = [Min|T],
	sel_sort(Rest,T).
	