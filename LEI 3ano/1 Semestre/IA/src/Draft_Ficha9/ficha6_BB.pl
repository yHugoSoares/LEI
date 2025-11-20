
%LICENCIATURA EM ENGENHARIA INFORMÁTICA
%MESTRADO integrado EM ENGENHARIA INFORMÁTICA

%Inteligência Artificial
%2025/26

%Draft Ficha 6


% Extensao do predicado filho: Filho,Pai -> {V,F}

filho( joao,jose ).
filho( jose,manuel ).
filho( carlos,jose ).
pai( paulo,filipe ).
pai( paulo,maria ).
avo( antonio,nadia ).
neto( nuno,ana ).
masculino( joao ).
masculino( jose ).
feminino( maria ).
feminino( joana ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado pai: Pai,Filho -> {V,F}

pai( P,F ) :- filho( F,P ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado avo: Avo,Neto -> {V,F}

avo ( A,N ) :- filho( N,X ), filho( X,A ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado bisavo: Bisavo,Bisneto -> {V,F}

bisavo( B,BN ) :- filho( BN,X ), filho( X,Y ), filho( Y,B ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado descendente: Descendente,Ascendente -> {V,F}

descendente( D,A ) :- filho( D,A ).
descendente( D,A ) :- descendente( X,A ), filho( D,X ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado descendente: Descendente,Ascendente,Grau -> {V,F}

descendenteG( D, A, G ) :- filho( D,A ), G is 1.
descendenteG( D, A, G ) :- descendenteG( X,A, G1 ), filho( D,X ), G is G1 + 1.