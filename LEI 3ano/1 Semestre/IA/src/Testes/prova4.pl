estudante(joao).

inscrito(Nome, Disciplina) :-
    estudante(Nome).

inscrito(joao, ia).

nota(Nome, Disciplina, Nota) :-
    inscrito(Nome, Disciplina).

nota(joao, ia, 15).

distincao(Nome) :-
    nota(Nome, ia, Nota),
    Nota >= 14.

desporto(Nome) :-
    estudante(Nome).

professor_leciona(Nome, Disciplina)