# 🏟️ Sistema de Gestão do Sport Clube "Os Beirões"
### Apresentação LI4 — 2025/2026
**Rui Cruz · Rafael Rodrigues · David Figueiredo · Hugo Soares**

---

## 1. Contexto e Problema

O **Sport Clube "Os Beirões"** é um pequeno clube de futebol da Vila de São Vicente da Beira,
gerido pelo Sr. Joaquim "Quim" Barrela — presidente, tesoureiro e faz-tudo.

### Problemas Identificados

| Área | Problema Real |
|---|---|
| **Gestão de Atletas** | Informação dispersa entre papel, Excel em pens perdidas e memória do Mister Zé |
| **Calendário** | Datas de treinos/jogos perdem-se em grupos de WhatsApp |
| **Convocatórias** | Feitas via WhatsApp, sem confirmações fiáveis — "exercício de adivinhação" |
| **Comunicação** | Avisos oficiais perdem-se no ruído de conversas informais |
| **Logística (Boleias)** | Caos de última hora nos jogos fora — jogadores ficam literalmente "a pé" |

### Restrições Intransigentes

1. **Baixa literacia digital** — Interface deve ser usável pelo Sr. Quim e pelo Mister Zé sem formação
2. **Orçamento zero** — Sem custos de servidores, licenças ou subscriptions
3. **Mobilidade** — Tudo deve funcionar bem no telemóvel (campo e balneário)
4. **Resiliência de dados** — Acabar com a "cabeça do treinador" como único backup

> **Decisão:** Estas 4 restrições guiaram todas as escolhas tecnológicas subsequentes.

---

## 2. Metodologia — Engenharia Assistida por LLM

### O que fizemos
Utilizámos **LLMs (Large Language Models)** como assistentes em todo o ciclo de engenharia,
mas com **supervisão crítica constante** da equipa.

### Como validámos os outputs

- Outputs rejeitados ou refinados sempre que introduziam **ambiguidades**
- Outputs corrigidos quando violavam o **método proposto pelo Prof. António Nestor Ribeiro**
- Outputs reformulados quando sacrificavam **detalhe por abrangência**

> **Justificação:** A dialética entre geração automática e revisão humana é uma conclusão
> metodológica central do projeto — o LLM acelera, mas não substitui o julgamento crítico.

---

## 3. Engenharia de Requisitos

### 3.1 Stakeholders Identificados

**Internos:**
- **Sr. Quim** (Presidente) — principal beneficiado, centralização da informação
- **Mister Zé** (Treinador) — utilizador operacional principal
- **Jogadores** — utilizadores finais (convocatórias, boleias, calendário)

**Externos:**
- **Associação de Futebol** — entidade reguladora (cumprimento de prazos e inscrições)

**Desenvolvimento:**
- **Equipa de desenvolvimento** — diretamente influenciada pelo resultado

> **Decisão:** Removemos "Dirigentes e Voluntários" dos stakeholders internos porque os condutores
> são restritos a utilizadores internos diretos. Adicionámos a equipa de desenvolvimento por ser
> igualmente afetada pelo outcome do projeto.

---

### 3.2 Requisitos Funcionais (16 RF)

| ID | Requisito | Stakeholder |
|---|---|---|
| RF01 | Registo de novos jogadores | Sr. Quim |
| RF02 | Consulta e edição de dados de jogadores | Sr. Quim |
| RF03 | Criação de eventos de treino | Mister Zé |
| RF04 | Registo de presenças em treinos | Mister Zé |
| RF05 | Criação de convocatórias para jogos | Mister Zé |
| RF06 | Resposta à convocatória (Vou/Não Vou) | Jogadores |
| RF07 | Oferta de boleia (viatura + lugares) | Proprietários |
| RF08 | Reserva de lugar em boleia | Jogadores |
| RF09 | Publicação de comunicados oficiais | Sr. Quim / Mister Zé |
| RF10 | Leitura de comunicados | Todos |
| RF11 | Autenticação no sistema | Todos |
| RF12 | Remoção de utilizadores | Sr. Quim |
| RF13 | Gestão de contactos de emergência | Sr. Quim |
| RF14 | Gestão de alterações de última hora | Mister Zé |
| RF15 | Gestão de ativos de transporte (viaturas) | Proprietários |
| RF16 | Registo histórico de resultados de jogos | Mister Zé |

---

### 3.3 Requisitos Não Funcionais (5 RNF)

| ID | Requisito | Justificação |
|---|---|---|
| RNF01 | Simplicidade de interface | Baixa literacia digital dos utilizadores principais |
| RNF02 | Otimização móvel | Uso em campo/balneário via telemóvel |
| RNF03 | Proteção de dados | Dados pessoais dos jogadores (RGPD) |
| RNF04 | Eficiência de custos | Orçamento zero — cloud free tier obrigatório |
| RNF05 | Integridade logística | Reservas de boleia sem race conditions |

---

### 3.4 Casos de Uso (18 UC)

Seguiu-se a **metodologia do Prof. António Nestor Ribeiro**, com 18 casos de uso atómicos
organizados em 4 subsistemas:

- **Gestão** — utilizadores, autenticação, comunicados
- **Eventos** — treinos, calendário
- **Operações Desportivas** — convocatórias, presenças, resultados
- **Logística** — boleias, viaturas

---

## 4. Arquitetura do Sistema

### 4.1 Estilo Arquitetural — 3 Camadas

```
┌─────────────────────────────────┐
│   PRESENTATION LAYER (Vue.js)   │  ← CSR no browser do utilizador
├─────────────────────────────────┤
│  BUSINESS LOGIC LAYER (Flask)   │  ← Python, padrão Facade + subsistemas
├─────────────────────────────────┤
│    DATA LAYER (PostgreSQL)      │  ← Acesso abstraído via DAOs
└─────────────────────────────────┘
```

> **Justificação:** A separação em 3 camadas independentes garante que cada componente pode ser
> testado, alterado e mantido isoladamente — essencial dado que a equipa é pequena e o sistema
> precisa de zero manutenção futura por parte do clube.

---

### 4.2 Decisões Tecnológicas e Justificações

#### Frontend — Vue.js com Client-Side Rendering (CSR)
- **Porquê Vue.js?** Framework leve, curva de aprendizagem rápida para a equipa, reatividade nativa
- **Porquê CSR?** Após o carregamento inicial, toda a navegação é instantânea no telemóvel
- **Risco identificado:** Dispositivos antigos podem ser lentos no primeiro carregamento
- **Mitigação:** Bundle otimizado e minificado no processo de build

#### Backend — Python com Flask
- **Porquê Python?** Produtividade elevada, ecossistema rico, familiaridade da equipa
- **Porquê Flask (micro-framework)?** Footprint mínimo — ideal para o hardware limitado do Raspberry Pi. Sem overhead desnecessário de um framework full-stack
- **Porquê não Django?** Django é mais pesado e tem features que não são necessárias neste contexto

#### Base de Dados — PostgreSQL
- **Porquê PostgreSQL?** Base de dados relacional robusta, ACID-compliant, gratuita
- **Porquê não SQLite?** SQLite não suporta concorrência adequadamente (race conditions nas boleias — RNF05)
- **Porquê não MongoDB?** Os dados são inerentemente relacionais (jogadores ↔ convocatórias ↔ jogos)

---

### 4.3 Infraestrutura — Raspberry Pi + Cloudflare Tunnel

```
[Utilizadores Mobile] ──HTTPS──> [Cloudflare Tunnel] ──> [Raspberry Pi]
                                                              ├── Flask (Gunicorn)
                                                              ├── Vue.js (build estático)
                                                              └── PostgreSQL
```

#### Raspberry Pi como Servidor de Produção
- **Porquê?** Custo único ~35€, consumo elétrico ~5W, sem mensalidades — **único hardware compatível com orçamento zero**
- **Risco:** Falha do cartão SD
- **Mitigação:** Política de backup híbrido diário (local + cloud gratuita)

#### Cloudflare Tunnel vs. Port Forwarding
- **Porquê Cloudflare Tunnel?** Gratuito, sem necessidade de IP estático, sem abertura de portas no router, TLS automático (HTTPS)
- **Porquê não Port Forwarding?** Expõe o IP real do clube, requer IP estático (custo), sem proteção DDoS

---

### 4.4 Padrões de Design

#### Padrão Facade (por subsistema)
```
BeiroesLNFacade  ←── API REST (Flask)
    ├── SSGestaoFacade
    ├── SSEventosFacade
    ├── SSOperacoesDesportivasFacade
    └── SSLogisticaFacade
```
> **Justificação:** O padrão Facade isola a camada de apresentação da lógica interna de cada
> subsistema. A API REST "fala" apenas com uma fachada, nunca diretamente com os DAOs.

#### Padrão DAO (Data Access Object)
> **Justificação:** Abstrai completamente o acesso à base de dados. Se no futuro se mudar de
> PostgreSQL para outro motor, só os DAOs mudam — a lógica de negócio não é afetada.

---

### 4.5 Política de Backup (Disaster Recovery)

| Aspeto | Decisão |
|---|---|
| **Frequência** | Backup diário automatizado (cron job) |
| **Destino** | Híbrido — local (pen USB) + cloud gratuita (Google Drive via rclone) |
| **Formato** | `pg_dump` comprimido |
| **RTO (Recovery Time Objective)** | < 2 horas em caso de falha física do SD |
| **Teste de recuperação** | Simulação periódica do processo de restore |

> **Justificação:** O Raspberry Pi tem um único ponto de falha físico (cartão SD). Sem backup,
> perdia-se toda a informação do clube — repetindo o problema original que o sistema veio resolver.

---

## 5. Implementação

### 5.1 Ambiente de Desenvolvimento

- **Docker** — containerização de todos os serviços (Flask + PostgreSQL) para ambiente reproduzível
- **GitHub Actions (self-hosted runner no Raspberry Pi)** — pipeline CI/CD automática
- **Fluxo:** `git push` → testes automáticos → deploy no Raspberry Pi

> **Justificação:** Docker garante que "funciona na minha máquina" = "funciona em produção".
> O self-hosted runner elimina custos de CI/CD em cloud.

### 5.2 Subsistema Implementado — Eventos

Implementação incremental e modular, começando pelo subsistema de Eventos como prova de conceito
da arquitetura completa (DAO → Facade → API → Vue.js).

---

## 6. Verificação e Validação

### 6.1 Estratégia de Testes

```
Testes Unitários (DAOs)
    ↓
Testes de Integração (Facades)
    ↓
Testes de Sistema (API REST)
    ↓
Testes de Aceitação (Cenários reais com Sr. Quim e Mister Zé)
```

### 6.2 Testes Unitários — Camada DAO
- `UtilizadorDAO` — CRUD de utilizadores
- `EventoDAO` — CRUD de eventos/treinos
- `ComunicadoDAO` — publicação e leitura de comunicados

### 6.3 Testes de Integração — Facades
- `SSGestaoFacade` + `SSEventosFacade`
- `SSLogisticaFacade`
- `BeiroesLNFacade` — **teste master** (`auto_test_ln_facade.py`)

### 6.4 Matriz de Rastreabilidade
Todos os 16 RF foram mapeados a testes concretos — garantindo cobertura funcional total.

### 6.5 Avaliação de Qualidade — ISO/IEC 25010
O sistema foi avaliado nas dimensões de Funcionalidade, Usabilidade, Fiabilidade, Eficiência
de Performance, Manutenibilidade e Portabilidade.

---

## 7. Problemas Encontrados e Soluções

| Problema | Como foi resolvido |
|---|---|
| LLM gerou requisitos ambíguos na SRS | Prompt corretivo específico; cópia exata dos requisitos já elicitados |
| LLM ignorou separação RF/RNF | Refinamento explícito do prompt com instrução de estrutura |
| LLM pouco desenvolveu o contexto inicial | Segundo prompt exigindo formato descritivo em prosa, ~1 página |
| Race conditions nas reservas de boleia | PostgreSQL com transações ACID + lógica de lock na camada DAO |
| Risco de falha do hardware (SD card) | Política de backup híbrido diário + RTO < 2h documentado |
| CI/CD com runner no Raspberry Pi | Primeira tentativa falhou → corrigida com configuração self-hosted |

---

## 8. Conclusão

| O que foi entregue |
|---|
| ✅ 16 Requisitos Funcionais + 5 Não Funcionais elicitados e formalizados (IEEE 29148) |
| ✅ 18 Casos de Uso atómicos especificados |
| ✅ Arquitetura de 3 camadas completamente validada |
| ✅ 11 Diagramas de Sequência detalhados |
| ✅ Protótipos de Facades e tabelas DAO implementados |
| ✅ Pipeline CI/CD funcional com self-hosted runner |
| ✅ Política de Backup e Disaster Recovery definida |

> O sistema está **pronto para a fase de codificação final** — a fundação arquitetural está
> validada e todas as decisões técnicas estão justificadas pelas restrições reais do clube.