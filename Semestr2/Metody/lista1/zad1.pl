ptak(_) :- fail.
ryba(_) :- fail.
dzdzownica(_) :- fail.

kot(my_cat).

lubi(X,Y) :- ptak(X),dzdzownica(Y).
lubi(X,Y) :- kot(X),ryba(Y).
lubi(X,Y) :- przyjaciel(X,Y).
przyjaciel(me,my_cat).
je(my_cat,X) :- lubi(my_cat,X).
