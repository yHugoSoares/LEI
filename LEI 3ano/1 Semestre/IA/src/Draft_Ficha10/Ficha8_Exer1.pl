%LICENCIATURA EM ENGENHARIA INFORMATICA
%MESTRADO integrado EM ENGENHARIA INFORMATICA

%Inteligencia Artificial
%2024/25

%Draft Ficha 8 Exercicio 1


aluno(1,joao,m).
aluno(2,antonio,m).
aluno(3,carlos,m).
aluno(4,luisa,f).
aluno(5,maria,f).
aluno(6,isabel,f).

curso(1,lei).
curso(2,miei).
curso(3,lcc).

%disciplina(cod,sigla,ano,curso)
disciplina(1,ed,2,1).
disciplina(2,ia,3,1).
disciplina(3,fp,1,2).

%inscrito(aluno,disciplina)
inscrito(1,1).
inscrito(1,2).
inscrito(5,3).
inscrito(5,5).
inscrito(2,5).

%nota(aluno,disciplina,nota)
nota(1,1,15).
nota(1,2,16).
nota(1,5,20).
nota(2,5,10).
nota(3,5,8).

%copia
copia(1,2).
copia(2,3).
copia(3,4).

% -------------------------------------------------------------------------
% Resolução Ficha 10 (baseada na Ficha 8)
% -------------------------------------------------------------------------

% i. Quais os alunos que não estão inscritos em qualquer disciplina
nao_inscrito(ID) :-
    aluno(ID, _, _),
    \+ inscrito(ID, _).

% ii. Quais os alunos que não estão inscritos em qualquer disciplina, 
% assumindo que um aluno inscrito numa disciplina que não existe não está inscrito
inscrito_valido(ID) :-
    inscrito(ID, D),
    disciplina(D, _, _, _).

nao_inscrito_total(ID) :-
    aluno(ID, _, _),
    \+ inscrito_valido(ID).

% iii. Qual a média de um determinado aluno
soma_lista([], 0).
soma_lista([H|T], S) :-
    soma_lista(T, S1),
    S is S1 + H.

comprimento_lista([], 0).
comprimento_lista([_|T], C) :-
    comprimento_lista(T, C1),
    C is C1 + 1.

media_aluno(ID, Media) :-
    findall(Nota, nota(ID, _, Nota), Notas),
    Notas \= [],
    soma_lista(Notas, Soma),
    comprimento_lista(Notas, Total),
    Media is Soma / Total.

% iv. Quais os alunos cuja média é acima da média (considere todas as notas de todas as disciplinas)
media_geral(Media) :-
    findall(Nota, nota(_, _, Nota), Notas),
    soma_lista(Notas, Soma),
    comprimento_lista(Notas, Total),
    Total > 0,
    Media is Soma / Total.

aluno_acima_media(ID) :-
    media_geral(MediaGeral),
    media_aluno(ID, MediaAluno),
    MediaAluno > MediaGeral.

% v. Quais os nomes dos alunos que copiaram
nome_copiador(Nome) :-
    copia(ID, _),
    aluno(ID, Nome, _).

nomes_copiadores(L) :-
    setof(Nome, nome_copiador(Nome), L).

% vi. Quais os alunos que copiaram (diretamente ou indiretamente) por um dado aluno
% copiou_de(Quem, DeQuem).
copiou_de(X, Y) :- copia(X, Y).
copiou_de(X, Y) :- copia(X, Z), copiou_de(Z, Y).

% vii. mapToNome - converter uma lista de números de alunos numa lista de nomes. 
% Assuma que podem ser dados números de alunos não registados (que devem ser ignorados).
mapToNome([], []).
mapToNome([ID|T], [Nome|TN]) :-
    aluno(ID, Nome, _),
    mapToNome(T, TN).
mapToNome([ID|T], TN) :-
    \+ aluno(ID, _, _),
    mapToNome(T, TN).
