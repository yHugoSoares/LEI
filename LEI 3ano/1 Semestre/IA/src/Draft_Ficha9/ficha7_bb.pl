%LICENCIATURA EM ENGENHARIA INFORMATICA
%MESTRADO integrado EM ENGENHARIA INFORMATICA

%Inteligencia Artificial
%2025/26

%Draft Ficha 7


% Parte I
%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Operacoes aritmeticas

%--------------------------------- - - - - - - - - - -  -  -  -  -   -

%--------------------------------- - - - - - - - - - -  -  -  -  -   -

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado soma: X,Y,Z,Soma -> {V,F}

soma( X,Y,Z,Soma ) :-
    Soma is X+Y+Z.



%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado somaL: L ,Soma -> {V,F}

somaL( [], 0 ).
somaL( [X|L], Soma ) :-
    somaL( L, Soma1 ),
    Soma is X + Soma1.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado maior: X,Y,R -> {V,F}

maior( X, Y, X) :-
    X >= Y.
maior( X, Y, Y) :-
    X < Y.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado maior: Lista, M, Resultado -> {V,}

maiorL( [X], X ).
maiorL( [X|L], M ) :-
    maiorL( L, M1 ),
    maior( X, M1, M ).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Quantidade de elementos de uma lista.

quantidade( [], 0 ).
quantidade( [X|L], N ) :-
    quantidade( L, N1 ),
    N is N1 + 1.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Tamanho de uma Lista

tamanho( L, N ) :-
    quantidade( L, N ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Média aritmética de uma lista

media( L, M ) :-
    somaL( L, S ),
    quantidade( L, N ),
    N > 0,
    M is S / N.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% verificar se um numero é par

par( N ) :-
    0 is N mod 2.

par2 (0).
par2 (N) :- 
    N > 0,
    N1 is N - 2,
    par2 (N1).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado impar: N -> {V,F}

impar( N ) :-
    1 is N mod 2.

impar2 (1).
impar2 (N) :- 
    N > 1,
    N1 is N - 2,
    impar2 (N1).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do ordena_crescente: Lista, Resultado -> {V,F}

ordena_crescente( [], [] ).
ordena_crescente( [X|L], R ) :-
    ordena_crescente( L, R1 ),
    inserir_ordenado( X, R1, R ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado inserir_ordenado: Elemento, Lista, Resultado -> {V,F}
inserir_ordenado( X, [], [X] ).
inserir_ordenado( X, [Y|L], [X,Y|L] ) :-
    X =< Y.
inserir_ordenado( X, [Y|L], [Y|R] ) :-
    X > Y,
    inserir_ordenado( X, L, R ).

% Parte II--------------------------------------------------------- - - - - -
%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado pertence: Elemento,Lista -> {V,F}

pertence( X,[X|L] ).
pertence( X,[Y|L] ) :
    X \= Y,
    pertence( X,L ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado comprimento: Lista,Comprimento -> {V,F}

comprimento ( [], 0 ).
comprimento ( [X|L], N ) :-
    comprimento( L, N1 ),
    N is N1 + 1.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado diferentes: Lista1,Lista2 -> {V,F}

diferentes ( [], _ ).
diferentes ( [X|L1], L2 ) :-
    \+ pertence( X, L2 ),
    diferentes ( L1, L2 ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado quantos: Lista,Comprimento -> {V,F}

quantos( L, N ) :-
    comprimento( L, N ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado apagar: Elemento,Lista,Resultado -> {V,F}

apagar( _, [], [] ).
apagar( X, [X|L], R ) :-
    apagar( X, L, R ).
apagar( X, [Y|L], [Y|R] ) :-
    X \= Y,
    apagar( X, L, R ).
          
%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado apagatudo: Elemento,Lista,Resultado -> {V,F}

apagatudo( _, [], [] ).
apagatudo( X, [X|L], R ) :-
    apagatudo( X, L, R ).
apagatudo( X, [Y|L], [Y|R] ) :-
    X \= Y,
    apagatudo( X, L, R ).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado adicionar: Elemento,Lista,Resultado -> {V,F}

adicionar( X, L, [X|L] ) :-
    \+ pertence( X, L ).
adicionar( X, L, L ) :-
    pertence( X, L ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado concatenar: Lista1,Lista2,Resultado -> {V,F}

concatenar( [], L2, L2 ).
concatenar( [X|L1], L2, [X|R] )
    :- concatenar( L1, L2, R ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado inverter: Lista,Resultado -> {V,F}

inverter( [], [] ).
inverter( [X|L], R ) :-
    inverter( L, R1 ),
    concatenar( R1, [X], R ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado sublista: SubLista,Lista -> {V,F}

sublista( S,L ) :-
    concatenar( _, L2, L ),
    concatenar( S, _, L2 ).