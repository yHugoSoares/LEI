<script>
import { ResultadoJogada } from "../models/resultadoJogada";
import Button from "./Button.vue";

export default {
  props: {
    jogo: {
      type: Object,
      required: true
    }
  },
  emits: ['jogadorAlterado', 'jogoTerminou', 'reset'],
  components: {
    Button
  },
  computed: {
    numColunas() {
      return this.jogo.constructor.NUMERO_COLUNAS;
    },
    numLinhas() {
      return this.jogo.constructor.NUMERO_LINHAS;
    }
  },
  methods: {
    jogar(coluna) {
      const res = this.jogo.jogar(coluna);
      if (res === ResultadoJogada.ERRO_COLUNACHEIA) {
        // coluna cheia -> nada a fazer (poderia mostrar mensagem)
        return;
      }

      // emitir que o jogador a jogar foi alterado
      this.$emit('jogadorAlterado', this.jogo.jogadorAJogar);

      // se a jogada terminou o jogo, emitir evento com o vencedor
      if (res === ResultadoJogada.TERMINOU) {
        this.$emit('jogoTerminou', this.jogo.vencedor);
      }
    },
    // novo wrapper que valida antes de jogar
    colClicked(coluna) {
      if (this.jogo.terminado) return;            // não jogar se jogo terminado
      if (this.jogo.tabuleiro[coluna].length >= this.numLinhas) return; // coluna cheia
      this.jogar(coluna);
    },
    reset() {
      this.jogo.reset();
      // emitir reset com o jogador que começa o novo jogo
      this.$emit('reset', this.jogo.jogadorAJogar);
      // também avisar quem é o jogador a jogar agora
      this.$emit('jogadorAlterado', this.jogo.jogadorAJogar);
    },
    aplicarVermelho(coluna, linha) {
      return this.jogo.getCelula(coluna, linha) === true ? 'red' : '';
    },
    aplicarAmarelo(coluna, linha) {
      return this.jogo.getCelula(coluna, linha) === false ? 'yellow' : '';
    }
  }
}
</script>

<template>
  <div class="game-wrap">
      <div class="tabuleiro">
        <div v-for="c in numColunas" :key="c" class="coluna" @click="colClicked(c-1)">
          <div v-for="l in numLinhas" :key="l" 
          :class="['celula', aplicarVermelho(c-1, l-1), aplicarAmarelo(c-1, l-1)]">
          </div>
        </div>
      </div>

      <div class="button-container">
        <Button @click="reset()">Reset</Button>
      </div>
  </div>
</template>
<style scoped>
.game-wrap {
  display:flex;
  flex-direction:column;
  align-items:center;
}

.tabuleiro { display:flex; gap:8px; padding:16px; background-color:#003366; border-radius:8px; box-shadow: 0 6px 18px rgba(0,0,0,0.12); }
.coluna { display:flex; flex-direction:column; gap:8px; cursor:pointer; }
.celula { width:48px; height:48px; border-radius:50%; background:#eee; border:1px solid #ccc; }
.celula.red { background: var(--color-red); }
.celula.yellow { background: var(--color-yellow); }
.button-container { margin-top:12px; display:flex; justify-content:center; width:100%; }

</style>