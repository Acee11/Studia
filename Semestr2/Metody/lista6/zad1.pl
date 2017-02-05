put_s(El, [], [El]).
put_s(El, Stack, [El|Stack]).

get_s([El|Stack], El, Stack).

addAll_s(El, Goal, Stack, ResStack) :-
	findall(El, Goal, L),
	append(L, Stack, ResStack).
empty_s([]).

empty_q(X-X).
get_q([H|T]-X, H, T-X).

put_q(E, X-[E|Y], X-Y).
%L - kolejka poczatkowa S - kolejka wynikowa

addAll_q(E,G,X-Y,X-Z):-
    findall(E,G,Y,Z).

g(1337).
g(9999).
g(505050).