:-arithmetic_function(!/1).
:- op(200, yf, !).

!(X,1) :- X =< 1, !.
!(X, Res) :- X1 is X - 1,!(X1, R1),  Res is X * R1.

:- arithmetic_function('!!'/1).
:- op(300, yf, '!!').

'!!'(X,1) :- X =< 1, !.
'!!'(X, Res) :- 1 is (X mod 2) , !, X1 is X - 2, '!!'(X1, R1), Res is R1 * X.
'!!'(X, Res) :- X1 is X - 1, '!!'(X1,Res).

