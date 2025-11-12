/* Este documento apresenta uma solução em construção. É fornecido como 
   material de estudo. Recomenda-se que o revejam e melhorem conforme   
   forem adquirindo novos conhecimentos. */

/* 
  Este ficheiro exporta um objeto que contém os resultados possíveis de uma jogada.
  TERMINOU - A jogada terminou o jogo.
  SUCESSO - A jogada foi realizada com sucesso e o jogo continua.
  ERRO_COLUNAINVALIDA - A coluna não é válida.
  ERRO_JOGOTERMINADO - O jogo já terminou.
  ERRO_COLUNACHEIA - A coluna já está cheia.
*/
export const ResultadoJogada = {
  TERMINOU: 0,
  SUCESSO: 1,
  ERRO_COLUNAINVALIDA: 2,
  ERRO_JOGOTERMINADO: 3,
  ERRO_COLUNACHEIA: 4
};