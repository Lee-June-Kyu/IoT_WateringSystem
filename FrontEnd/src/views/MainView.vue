<template>
  <v-app>
    <div class="box">
      <v-icon color="#BCE29E" x-large>fas fa-seedling</v-icon>
      <h1 class="main__text">Welcome to Smart Farm</h1>
    </div>
  </v-app>
</template>

<script>
export default {
  name: 'Main'
}
</script>
<style scoped>
.box {
  width: 80vw;
  height: 90vh;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
}
.main__text {
  font-size: 90px;
}
</style>
