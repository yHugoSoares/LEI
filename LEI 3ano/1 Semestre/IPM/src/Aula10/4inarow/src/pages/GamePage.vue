<script>
import { Game } from "../models/game";
import { PlayResult } from "../models/playResult";
import { GameResult } from "../models/gameResult";

export default {
  data() {
    return {
      game: new Game(),
      statistics: {}
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
      
    },
    async updateStatistics() {
      
    },
    async saveGame() {
      
    },
    play(column) {
      const res = this.game.play(column);

      if (res === PlayResult.ERROR_FULL_COLUMN) {
        alert('Column is full!');
      } else if (res === PlayResult.ERROR_GAME_OVER) {
        alert('Game over. Click "New Game" to play another game.')
      } else if (res === PlayResult.GAME_OVER) {
        this.updateStatistics();
        this.saveGame();
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