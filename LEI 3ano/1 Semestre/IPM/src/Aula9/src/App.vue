<!-- Este documento apresenta uma solução em construção. É fornecido como 
     material de estudo. Recomenda-se que o revejam e melhorem conforme   
     forem adquirindo novos conhecimentos. -->

<script>
import OJogo from './components/OJogo.vue';
import Navbar from './components/Navbar.vue';
import { Jogo } from './models/jogo';

export default {
  components: {
    Navbar,
    OJogo
  },
  data() {
    const jogo = new Jogo();
    return {
      jogo,
      jogadorAJogar: jogo.jogadorAJogar,
      vencedor: jogo.vencedor
    }
  },
  methods: {
    onJogadorAlterado(novoJogador) {
      this.jogadorAJogar = novoJogador;
      // garantir também que o modelo original fica sincronizado (opcional)
      this.jogo.jogadorAJogar = novoJogador;
    },
    onJogoTerminou(vencedor) {
      this.vencedor = vencedor;
      // sincronizar modelo
      this.jogo.vencedor = vencedor;
    },
    onReset(jogadorInicial) {
      this.jogadorAJogar = jogadorInicial;
      this.vencedor = null;
      // sincronizar modelo já feito pelo OJogo via jogo.reset()
    }
  }
}
</script>

<template>
  <div class="app-root">
    <Navbar :jogadorAJogar="jogadorAJogar" :vencedor="vencedor" />

    <!-- center the game area below the navbar -->
    <div class="center-wrapper">
      <OJogo :jogo="jogo"
             @jogadorAlterado="onJogadorAlterado"
             @jogoTerminou="onJogoTerminou"
             @reset="onReset" />
    </div>
  </div>
</template>

<style scoped>
/* Root fills the viewport, keeps navbar at top and centers the game area */
.app-root {
  min-height: 100vh;
  display: flex;
  flex-direction: column;
}

.center-wrapper {
  /* allow this area to take remaining vertical space and center content */
  flex: 1 1 auto;
  display: flex;
  align-items: center;
  justify-content: center;
  padding: 1rem;
}
</style>