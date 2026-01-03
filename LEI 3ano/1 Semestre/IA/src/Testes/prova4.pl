estudante(joao).

inscrito(joao, ia).

nota(joao, ia, 15).

distincao(Nome, Disciplina) :-
    nota(Nome, Disciplina, Nota),
    Nota >= 14.

desporto(Nome) :-
    estudante(Nome).

professor_leciona(_, Disciplina) :-
    inscrito(_, Disciplina).


distincao_em_ia(Nome) :-
    distincao(Nome, ia).


disciplinas_nome(Nome, Count) :-
    findall(Disciplina, inscrito(Nome, Disciplina), Disciplinas),
    length(Disciplinas, Count).



% ============================= Grupo 2 ============================= %

animal(gato).
animal(cão).
animal(pardal).

mamífero(gato).
mamífero(cão).

ave(pardal).

voa(pardal).
voa(X) :- ave(X), não_prejudicado(X).

prejudicado(pinguim).

não_prejudicado(X) :- animal(X), \+ prejudicado(X).