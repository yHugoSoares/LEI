<script>
import { Game } from "../models/game";
import { PlayResult } from "../models/playResult";
import { GameResult } from "../models/gameResult";

export default {
  data() {
    return {
      game: new Game(),
      statistics: {},
      simulation: {},
      startPlayer: false,
      plays: []
    }
  },
  methods: {
    async getStatistics() {
      try {
        const response = await fetch('http://localhost:3000/statistics/1');

        if (!response.ok) {
          throw new Error('Something went wrong');
        }

        this.statistics = await response.json();
      } catch (error) {
        console.log(error);
      }
    },
    async updateSimulation() {
      try {
        const payload = {
          startPlayer: this.startPlayer,
          plays: this.plays
        };

        const response = await fetch('http://localhost:3000/simulation/1', {
          method: 'PATCH',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify(payload)
        });

        if (!response.ok) {
          throw new Error('Failed to update simulation');
        }

        // guardar resposta localmente (útil para debug)
        this.simulation = await response.json();
      } catch (error) {
        console.error(error);
      }
    },
    async updateStatistics() {
      try {
        // Garantir valores iniciais
        const stats = this.statistics || {};
        let red = Number(stats.red) || 0;
        let yellow = Number(stats.yellow) || 0;
        let draw = Number(stats.draw) || 0;

        // Incrementar conforme vencedor do jogo atual
        if (this.game.winner === GameResult.RED) {
          red++;
        } else if (this.game.winner === GameResult.YELLOW) {
          yellow++;
        } else if (this.game.winner === GameResult.DRAW) {
          draw++;
        }

        const response = await fetch('http://localhost:3000/statistics/1', {
          method: 'PATCH',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ red, yellow, draw })
        });

        if (!response.ok) {
          throw new Error('Failed to update statistics');
        }

        // Atualizar estado local com o registo retornado
        this.statistics = await response.json();
      } catch (error) {
        console.error(error);
      }
    },
    async saveGame() {
      try {
        const payload = {
          game: {
            board: this.game.board,
            player: this.game.player,
            winner: this.game.winner,
            isOver: this.game.isOver
          },
          date: new Date().toISOString()
        };

        const response = await fetch('http://localhost:3000/games', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify(payload)
        });

        if (!response.ok) {
          throw new Error('Failed to save game');
        }

        const saved = await response.json();
        console.log('Game saved:', saved);
      } catch (error) {
        console.error(error);
      }
    },
    async play(column) {
      const res = this.game.play(column);

      if (res === PlayResult.ERROR_FULL_COLUMN) {
        alert('Column is full!');
      } else if (res === PlayResult.ERROR_GAME_OVER) {
        alert('Game over. Click "New Game" to play another game.')
      } else if (res === PlayResult.GAME_OVER) {
        // registar a última jogada
        this.plays.push(column);
        await this.updateStatistics();
        await this.saveGame();
        await this.updateSimulation();
      } else if (res === PlayResult.SUCCESS) {
        // registar jogada normal
        this.plays.push(column);
      }
    },
    reset() {
      this.game.reset();
      this.startPlayer = this.game.player;
      this.plays = [];
      this.updateSimulation();
    }
  },
  computed: {
    gameStatus() {
      const winner = this.game.winner;

      if (winner === GameResult.YELLOW) {
        return 'Winner: Yellow';
      }

      if (winner === GameResult.RED) {
        return 'Winner: Red';
      }

      if (winner === GameResult.DRAW) {
        return 'Draw';
      }

      return this.game.player
        ? 'Player: Red'
        : 'Player: Yellow'
    }
  },
  created() {
    this.getStatistics();
    this.startPlayer = this.game.player;
  }
}
</script>

<template>
  <div class="status">{{ gameStatus }}</div>
  <game-board :game="game" @play="play" />
  <div class="button-container">
    <button-component @click="reset">New Game</button-component>
  </div>
</template>

<style scoped>
.status {
  font-size: 1.2rem;
  font-weight: 600;
  text-align: center;
  margin: 40px 0;
}

.button-container {
  display: flex;
  justify-content: center;
  margin-top: 40px;
}
</style>