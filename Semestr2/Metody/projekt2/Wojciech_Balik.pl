literal(P) :-
	atom(P).
literal(~_).

setToClause([[],[]],[]) :- !.
setToClause([[],[P|[]]], P) :- !.
setToClause([[],[P|PT]], P v Q) :-
	!,
	setToClause([[],PT], Q).
setToClause([[N|[]], []], ~N) :- !.
setToClause([ [N|[]], PT ],~N v Q) :-
	!,
	setToClause([[],PT],Q).
setToClause([[N|NT],Positive],~N v Q) :-
	setToClause([NT,Positive], Q).

clauseToList(P,[P]) :- literal(P),!.
clauseToList(P v Q,[P|T]) :-
	clauseToList(Q,T).

finalClause([],[[],[]]).
finalClause([~H|T],[[H|Negative],Positive]) :-	
	!,
	finalClause(T,[Negative,Positive]).
finalClause([H|T],[Negative,[H|Positive]]) :-
	finalClause(T,[Negative,Positive]).

addToQueue(X,[],[X]) :-
	!.
addToQueue((Num,Clause,Type,ClauseLen), [(HNum,HCl,HType,HClLen)|T], [(Num,Clause,Type,ClauseLen),(HNum,HCl,HType,HClLen)|T]) :-
    HClLen >= ClauseLen,
    !.
addToQueue((Num,Clause,Type,ClauseLen),[H|T],[H|R1]) :-
    addToQueue((Num,Clause,Type,ClauseLen),T,R1).

makeQueue([],X,X) :- !.
makeQueue([H|T],X,R) :-
    addToQueue(H,X,X1),
    makeQueue(T,X1,R).

do_I_need_this(_, []).
do_I_need_this( [Neg, Pos], [(_,[CNeg, CPos],_,_) | _]) :-
	ord_subset(CNeg,Neg),
	ord_subset(CPos,Pos),
	!,
	fail.
do_I_need_this(CL, [_|T]) :-
	do_I_need_this(CL, T).


tautology([Neg, Pos]) :-
	member(X,Neg),
	member(X,Pos),
	!.
    
    
result([Neg1,Pos1], [Neg2,Pos2], [NegRes,PosRes]) :-
	(
		member(X,Neg1),
		member(X,Pos2),
		ord_subtract(Neg1,[X],Neg1New),
		ord_subtract(Pos2,[X],Pos2New),
		ord_union(Neg1New,Neg2,NegRes),
		ord_union(Pos1,Pos2New,PosRes)
	);
	(
		member(X, Pos1),
		member(X, Neg2),
		ord_subtract(Pos1,[X],Pos1New),
		ord_subtract(Neg2,[X],Neg2New),
		ord_union(Pos1New,Pos2,PosRes),
		ord_union(Neg1,Neg2New,NegRes)
	).

init([],_,[]).
init([Clause|T], Num, [(Num,NClause,axiom,ClauseLen)|T1]) :-
	clauseToList(Clause,ClList),
	list_to_ord_set(ClList,ClSet),
	finalClause(ClSet,NClause),
	length(ClSet,ClauseLen),
    N1 is Num + 1,
    init(T,N1,T1).

       
createProofList(_, [], [], _, _) :- !.
 
createProofList(  (Num, Clause, _, _),  [(Num1, Clause1, _, _)|T],  [(NumRes, [Negative,Positive], (Num,Num1), ResLen)|TRes], Mem,  Number   ) :-
    result(Clause,Clause1, [Negative, Positive]),
    do_I_need_this([Negative, Positive], Mem),
    \+tautology([Negative, Positive]),
    !,
    length(Positive,N1),
    length(Negative,N2),
    ResLen is N1 + N2,
    NumRes is Number + 1,
    createProofList((Num, Clause, _, _), T, TRes,[(NumRes, [Negative, Positive], (Num,Num1), ResLen) | Mem],NumRes).

createProofList( (Num, Clause, _, _), [_ | T],TRes, Mem, Number) :-
    createProofList((Num, Clause, _, _), T, TRes, Mem, Number).

createFullProof(Queue, ProofList, Result) :-
	createFullProof([],Queue, ProofList, Result).

createFullProof(_, [], _, _) :- !,fail.
createFullProof(A, [QHead|QT], ProofList, Result) :-
    length(ProofList,N),
    createProofList(QHead,A,R1,ProofList,N),
    (
    	(    		
    		member((_,[[],[]],_,_),R1),
    		!,
    		append(ProofList,R1,Result)
    	);
    	(	    		    		

    		append(ProofList,R1,NewPList),
    		makeQueue(R1,QT,NewQueue),
    		createFullProof([QHead|A], NewQueue, NewPList, Result)
    	)
    ).

finishProof([],[]).
finishProof( [(_, [Positive,Negative], Type, _) | ClTail],[(Clause, Type) | RTail]) :-
	setToClause([Positive,Negative],Clause),
    finishProof(ClTail, RTail).        
    
prove(Clauses, Proof) :-
    init(Clauses, 1, L), %przeksztalcanie klauzuli w postaci l1 v l2 v ... v ln do postaci (nr klauzuli, [[literaly negatywne],[literaly pozytywne]], pochodzenie, ilosc literalow)
    makeQueue(L,[],Queue),
    createFullProof(Queue, L, ProofAlpha),
    finishProof(ProofAlpha, Proof).
    %writeProof(Proof).
