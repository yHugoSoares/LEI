<script>
import { Game } from "../models/game.js";

export default {
  props: ['id'],
  data() {
    return {
      game: new Game()
    };
  },
  methods: {
    async getGame() {
      try {
        const id = this.id || this.$route.params.id;
        if (!id) return;

        const response = await fetch(`http://localhost:3000/games/${id}`);
        if (!response.ok) throw new Error('Failed to fetch game');

        const data = await response.json();
        const gameObj = data.game || {};
        const gameInstance = new Game();
        gameInstance.board = gameObj.board || gameInstance.board;
        gameInstance.player = typeof gameObj.player !== 'undefined' ? gameObj.player : gameInstance.player;
        gameInstance.winner = typeof gameObj.winner !== 'undefined' ? gameObj.winner : gameInstance.winner;
        gameInstance.isOver = typeof gameObj.isOver !== 'undefined' ? gameObj.isOver : gameInstance.isOver;

        this.game = gameInstance;
      } catch (error) {
        console.error(error);
      }
    }
  },
  created() {
    this.getGame();
  }
}
</script>

<template>
  <game-board :game="game"></game-board>
</template>