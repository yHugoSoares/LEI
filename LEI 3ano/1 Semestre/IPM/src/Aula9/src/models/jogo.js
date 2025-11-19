/* Este documento apresenta uma solução em construção. É fornecido como 
   material de estudo. Recomenda-se que o revejam e melhorem conforme   
   forem adquirindo novos conhecimentos. */

/* 
Importa o objeto ResultadoJogada do ficheiro resultadoJogada.js e o objeto ResultadoJogo do ficheiro resultadoJogo.js.
*/
import { ResultadoJogada } from "./resultadoJogada";
import { ResultadoJogo } from "./resultadoJogo";

/* 
Este ficheiro exporta uma classe Jogo que representa o jogo 4 em linha.
*/
export class Jogo {
  static NUMERO_COLUNAS = 7;
  static NUMERO_LINHAS = 6;

  tabuleiro = [];         // Array de arrays com o estado do tabuleiro.
  jogadorAJogar = false;  // Indica o jogador que tem a vez de jogar. false - jogador amarelo, true - jogador vermelho.
  vencedor = null;        // Indica o vencedor do jogo (cf. ResultadoJogo). null - jogo em curso.
  terminado = false;      // Indica se o jogo terminou.

  constructor() {
    this.reset();
  }

  jogar(coluna) {
    if (this.terminado) {
      return ResultadoJogada.ERRO_JOGOTERMINADO;
    }

    if (coluna < 0 || coluna >= Jogo.NUMERO_COLUNAS) {
      return ResultadoJogada.ERRO_COLUNAINVALIDA;
    }

    if (this.tabuleiro[coluna].length == Jogo.NUMERO_LINHAS) {
      return ResultadoJogada.ERRO_COLUNACHEIA;
    }

    this.tabuleiro[coluna].push(this.jogadorAJogar);
    this.jogadorAJogar = !this.jogadorAJogar;
    this.validarSeTerminou();

    return this.terminado ? ResultadoJogada.TERMINOU : ResultadoJogada.SUCESSO;
  }

  validarSeTerminou() {
    // Reset antes de verificar
    this.vencedor = null;
    this.terminado = false;

    for (let c = 0; c < this.tabuleiro.length; c++) {
      for (let l = 0; l < Jogo.NUMERO_LINHAS; l++) {
        // Linha (direita)
        let linhaStr = this.getCoordenadasLinha(c, l)
                          .map((x) => this.getCelulaInterna(x[0], x[1]))
                          .join("");
        if (linhaStr.includes("falsefalsefalsefalse")) {
          this.vencedor = ResultadoJogo.AMARELO;
          this.terminado = true;
          return;
        }
        if (linhaStr.includes("truetruetruetrue")) {
          this.vencedor = ResultadoJogo.VERMELHO;
          this.terminado = true;
          return;
        }

        // Coluna (para cima)
        let colunaStr = this.getCoordenadasColuna(c, l)
                          .map((x) => this.getCelulaInterna(x[0], x[1]))
                          .join("");
        if (colunaStr.includes("falsefalsefalsefalse")) {
          this.vencedor = ResultadoJogo.AMARELO;
          this.terminado = true;
          return;
        }
        if (colunaStr.includes("truetruetruetrue")) {
          this.vencedor = ResultadoJogo.VERMELHO;
          this.terminado = true;
          return;
        }

        // Diagonal superior (ascendente)
        let diagSupStr = this.getCoordenadasDiagonalSuperior(c, l)
                          .map((x) => this.getCelulaInterna(x[0], x[1]))
                          .join("");
        if (diagSupStr.includes("falsefalsefalsefalse")) {
          this.vencedor = ResultadoJogo.AMARELO;
          this.terminado = true;
          return;
        }
        if (diagSupStr.includes("truetruetruetrue")) {
          this.vencedor = ResultadoJogo.VERMELHO;
          this.terminado = true;
          return;
        }

        // Diagonal inferior (descendente)
        let diagInfStr = this.getCoordenadasDiagonalInferior(c, l)
                          .map((x) => this.getCelulaInterna(x[0], x[1]))
                          .join("");
        if (diagInfStr.includes("falsefalsefalsefalse")) {
          this.vencedor = ResultadoJogo.AMARELO;
          this.terminado = true;
          return;
        }
        if (diagInfStr.includes("truetruetruetrue")) {
          this.vencedor = ResultadoJogo.VERMELHO;
          this.terminado = true;
          return;
        }
      }
    }

    // Verificar empate (tabuleiro cheio)
    if (this.tabuleiroCheio()) {
      this.terminado = true;
      this.vencedor = ResultadoJogo.EMPATE;
    } else {
      this.terminado = false;
      this.vencedor = null;
    }
  }

  getCelula(coluna, linha) {
    let linhaInversa = Jogo.NUMERO_LINHAS - linha - 1;
    return this.getCelulaInterna(coluna, linhaInversa);
  }

  getCelulaInterna(coluna, linha) {
    return coluna < 0 || coluna >= Jogo.NUMERO_COLUNAS || linha < 0 || linha >= Jogo.NUMERO_LINHAS ?
        'null' :
        (typeof this.tabuleiro[coluna][linha] === 'undefined' ? 'null' : this.tabuleiro[coluna][linha]);
  }

  getCoordenadasLinha(coluna, linha) {
    // 4 posições na mesma linha, a partir da coluna indicada
    return [
      [coluna, linha],
      [coluna + 1, linha],
      [coluna + 2, linha],
      [coluna + 3, linha]
    ];
  }
  
  getCoordenadasColuna(coluna, linha) {
    // 4 posições na mesma coluna, a partir da linha indicada (para cima)
    return [
      [coluna, linha],
      [coluna, linha + 1],
      [coluna, linha + 2],
      [coluna, linha + 3]
    ];
  }
  
  getCoordenadasDiagonalSuperior(coluna, linha) {
    // diagonal ascendente: (c,l), (c+1,l+1), (c+2,l+2), (c+3,l+3)
    return [
      [coluna, linha],
      [coluna + 1, linha + 1],
      [coluna + 2, linha + 2],
      [coluna + 3, linha + 3]
    ];
  }
  
  getCoordenadasDiagonalInferior(coluna, linha) {
    // diagonal descendente: (c,l), (c+1,l-1), (c+2,l-2), (c+3,l-3)
    return [
      [coluna, linha],
      [coluna + 1, linha - 1],
      [coluna + 2, linha - 2],
      [coluna + 3, linha - 3]
    ];
  }
  
  tabuleiroCheio() {
    // verdadeiro se todas as colunas têm número máximo de linhas preenchidas
    return this.tabuleiro.every(col => col.length === Jogo.NUMERO_LINHAS);
  }

  reset() {
    // inicializa as colunas vazias
    this.tabuleiro = [];
    for (let i = 0; i < Jogo.NUMERO_COLUNAS; i++) {
      this.tabuleiro.push([]);
    }
    this.terminado = false;
    this.jogadorAJogar = false; // começa o jogador amarelo por defeito
    this.vencedor = null;
  }
}