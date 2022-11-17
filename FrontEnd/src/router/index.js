import Vue from 'vue'
import VueRouter from 'vue-router'
import MainView from '../views/MainView.vue'
import MainView1 from '../views/Main1View.vue'
import MainView2 from '../views/Main2View.vue'

Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    name: 'Main',
    component: MainView
    // children: [{ path: '/:id', component: MainView }]
  },
  {
    path: '/1',
    name: 'Main1',
    component: MainView1
    // children: [{ path: '/:id', component: MainView }]
  },
  {
    path: '/2',
    name: 'Main2',
    component: MainView2
    // children: [{ path: '/:id', component: MainView }]
  }
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

export default router
