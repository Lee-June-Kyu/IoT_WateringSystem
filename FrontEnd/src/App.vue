<template>
  <v-app>
    <SideBar />

    <v-main>
      <router-view />
    </v-main>
  </v-app>
</template>

<script>
import SideBar from '../src/components/SideBar.vue'
export default {
  name: 'App',
  components: {
    SideBar
  },

  data: () => ({
    //
  })
}
</script>
<style>
* {
  font-family: 'Jua', sans-serif;
}
</style>
