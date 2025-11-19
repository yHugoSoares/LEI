<script>
import { Game } from "../models/game";

export default {
  data() {
    return {
      game: new Game(),
      running: false,
      simulation: {},
      intervalId: null
    }
  },
  methods: {
    play(column) {
      this.game.play(column);
    },
    async simulate() {
      try {
        if (this.running) return;

        if (!this.simulation || !Array.isArray(this.simulation.plays) || this.simulation.plays.length === 0) {
          alert('No simulation available');
          return;
        }

        // Reset board and set starting player
        this.game = new Game();
        this.game.player = !!this.simulation.startPlayer;
        this.running = true;

        let idx = 0;
        this.intervalId = setInterval(() => {
          if (idx >= this.simulation.plays.length) {
            clearInterval(this.intervalId);
            this.intervalId = null;
            this.running = false;
            return;
          }
          const col = this.simulation.plays[idx++];
          this.game.play(col);
        }, 500);
      } catch (err) {
        console.error(err);
        this.running = false;
        if (this.intervalId) {
          clearInterval(this.intervalId);
          this.intervalId = null;
        }
      }
    },
    async getSimulation() {
      try {
        const response = await fetch('http://localhost:3000/simulation/1');
        if (!response.ok) throw new Error('Failed to fetch simulation');
        this.simulation = await response.json();
      } catch (err) {
        console.error(err);
        this.simulation = {};
      }
    }
  },
  created() {
    this.getSimulation();
  },
  unmounted() {
    if (this.intervalId) {
      clearInterval(this.intervalId);
      this.intervalId = null;
    }
  }
}
</script>

<template>
<div class="title">Simulate Last Game</div>
  <game-board :game="game"></game-board>
  <div class="button-container">
    <button-component @click="simulate" :disabled="running">Simulate</button-component>
  </div>
</template>

<style scoped>
.title {
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