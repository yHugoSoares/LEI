<script>
import { ResultadoJogo } from "../models/resultadoJogo";

export default {
  props: ['jogadorAJogar', 'vencedor'],
  computed: {
    statusMessage() {
      // jogo ainda em curso -> mostrar quem joga
      if (this.vencedor === null || typeof this.vencedor === 'undefined') {
        return this.jogadorAJogar ? 'Vez: Vermelho' : 'Vez: Amarelo';
      }
      // jogo terminou -> mostrar resultado
      switch (this.vencedor) {
        case ResultadoJogo.VERMELHO: return 'Vencedor: Vermelho';
        case ResultadoJogo.AMARELO: return 'Vencedor: Amarelo';
        case ResultadoJogo.EMPATE: return 'Empate';
        default: return '';
      }
    }
    , statusClass() {
      // when game ongoing, color by current player; when finished, color by winner
      if (this.vencedor === null || typeof this.vencedor === 'undefined') {
        return this.jogadorAJogar ? 'status--red' : 'status--yellow';
      }
      switch (this.vencedor) {
        case ResultadoJogo.VERMELHO: return 'status--red';
        case ResultadoJogo.AMARELO: return 'status--yellow';
        case ResultadoJogo.EMPATE: return 'status--tie';
        default: return '';
      }
    }
  }
}
</script>

<template>
  <nav class="navbar">
    <div class="brand">4 em linha</div>
    <div class="status" :class="statusClass">{{ statusMessage }}</div>
  </nav>
</template>

<style scoped>
.navbar {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 12px 20px;
  background: #ffffff;
  border-bottom: 1px solid rgba(0,0,0,0.06);
  box-shadow: 0 2px 6px rgba(0,0,0,0.04);
}
.brand {
  font-weight: 800;
  letter-spacing: 0.3px;
}
.status {
  font-weight: 600;
}
.button {
  border: 1px solid black;
  border-radius: 5px;
  text-align: center;
  padding: 10px;
  font-weight: 600;
}
.status--red {
  background: #c62828; /* red */
  color: #ffffff;
  padding: 6px 10px;
  border-radius: 6px;
}
.status--yellow {
  background: #ffeb3b; /* yellow */
  color: #111111;
  padding: 6px 10px;
  border-radius: 6px;
}
.status--tie {
  background: #9e9e9e;
  color: #ffffff;
  padding: 6px 10px;
  border-radius: 6px;
}
</style>