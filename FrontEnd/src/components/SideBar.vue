<template>
  <v-navigation-drawer v-model="drawer" permanent app>
    <v-list-item class="px-2 py-5">
      <v-list-item-title class="text-capitalize" align="center">
        <v-icon color="#BCE29E">fas fa-seedling</v-icon>
        <h2>Smart Farm</h2>
      </v-list-item-title>
    </v-list-item>
    <v-list nav dense>
      <v-list-item-group v-model="selectedItem" color="#749F82">
        <v-list-item v-for="(item, i) in plantsdata" :key="i" @click="go(item.id)">
          <v-list-item-content>
            <v-list-item-title align="center" v-text="item.plant_name"></v-list-item-title>
          </v-list-item-content>
        </v-list-item>
      </v-list-item-group>
    </v-list>
  </v-navigation-drawer>
</template>

<script>
import axios from 'axios'
export default {
  name: 'SideBar',

  data: () => ({
    selectedItem: 0,
    drawer: null,
    plantsdata: []
  }),
  created() {
    this.GetPlants()
  },
  methods: {
    async GetPlants() {
      await axios
        .get(process.env.VUE_APP_API + '/web/plants')
        .then(res => {
          console.log(res.data.data)
          this.plantsdata = res.data.data
        })
        .catch(error => {
          console.log('Error: plants', error)
        })
    },
    go(id) {
      this.$router.push(`/content/${id}`)
    }
  }
}
</script>
<style scoped></style>
