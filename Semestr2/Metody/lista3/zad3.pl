factorial(N,1) :-
	N < 1.
factorial(N, Res) :-
	N > 0,
	X is N-1,
	factorial(X, Y),
	Res is N * Y.

%decimal(Dig, Num) :-
%	decimal(Dig,[],Num).

decimal(Num, Digits) :-
	decimal(Num,[],Digits).

decimal(0,[],[0]) :- !.
decimal(0,X,X) :- !.
decimal(Num, R, Dig) :-
	H is Num mod 10,
	X is Num // 10,
	decimal(X,[H|R],Dig).

concat_number(Dig,Num) :-
	reverse(Dig,Gid),
	concat_number(Gid,1,Num).

concat_number([0],1,0) :- !.
concat_number([],W,0) :- W > 1.
concat_number([H|T],W,Num) :-
	NewW is W * 10,
	concat_number(T,NewW,R),
	Num is (H * W) + R.



	
	
