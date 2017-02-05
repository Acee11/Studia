slowo(L,N) --> [a], slowo1([b|L],N1),{N is N1 + 1}.
slowo1([b|T],0) --> [b],T.
slowo1(B,N) --> slowo(B,N).
slowo([],0) --> [].



