import { createRouter, createWebHistory } from 'vue-router';
import GamePage from './pages/GamePage.vue';
import StatisticsPage from './pages/StatisticsPage.vue';
import SimulationPage from './pages/SimulationPage.vue';
import NotFoundPage from './pages/NotFoundPage.vue';

const routes = [
  { path: '/', redirect: '/game' },
  { path: '/game', component: GamePage },
  { path: '/statistics', component: StatisticsPage },
  { path: '/simulation', component: SimulationPage },
  { path: '/:pathMatch(.*)*', component: NotFoundPage }
];

const router = createRouter({
  history: createWebHistory(),
  routes
});

export default router;