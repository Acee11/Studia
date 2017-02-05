:- op(910, yfx).


expression(mult(X, Y)) --> simple_expression(X), "*", !, expression(Y).
expression(X) --> simple_expression(X).
simple_expression(a) --> "a".
simple_expression(b) --> "b".


test(X, Res) :-
	atom_codes(X,S),
	phrase(expression(Res),S).