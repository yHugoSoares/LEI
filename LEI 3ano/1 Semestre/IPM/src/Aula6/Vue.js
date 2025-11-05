const { createApp } = Vue;

createApp({
  data() {
    return {
      board: Array(9).fill(''),
      currentPlayer: 'X',
      gameOver: false,
      finalMessage: null
    };
  },
  computed: {
    statusText() {
      if (this.finalMessage) return this.finalMessage;
      return `Turno: ${this.currentPlayer}`;
    }
  },
  methods: {
    handleCellClick(idx) {
      if (this.gameOver) {
        window.alert('Jogo Terminado! Faça reset para recomeçar.');
        return;
      }
      if (this.board[idx]) {
        window.alert('Célula já preenchida');
        return;
      }
      this.board.splice(idx, 1, this.currentPlayer);

      const winner = this.checkWinner(this.board);
      if (winner === 'X' || winner === 'O') {
        this.finalMessage = `${winner} venceu`;
        this.gameOver = true;
        window.alert(`Vencedor: ${winner}`);
        return;
      } else if (winner === 'draw') {
        this.finalMessage = 'Empate';
        this.gameOver = true;
        window.alert('Empate');
        return;
      }

      this.currentPlayer = this.currentPlayer === 'X' ? 'O' : 'X';
    },
    resetGame() {
      this.board = Array(9).fill('');
      this.currentPlayer = 'X';
      this.gameOver = false;
      this.finalMessage = null;
    },
    checkWinner(b) {
      const combos = [
        [0,1,2],[3,4,5],[6,7,8],
        [0,3,6],[1,4,7],[2,5,8],
        [0,4,8],[2,4,6]
      ];
      for (const [a,bb,c] of combos) {
        if (b[a] && b[a] === b[bb] && b[a] === b[c]) {
          return b[a];
        }
      }
      if (b.every(cell => cell)) return 'draw';
      return null;
    }
  }
}).mount('#app');