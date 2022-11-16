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
        <v-list-item v-for="(item, i) in items" :key="i">
          <v-list-item-content>
            <v-list-item-title align="center" v-text="item.text"></v-list-item-title>
          </v-list-item-content>
        </v-list-item>
      </v-list-item-group>
    </v-list>
  </v-navigation-drawer>
</template>

<script>
export default {
  name: 'SideBar',

  data: () => ({
    selectedItem: 0,
    drawer: null,
    items: [
      { text: 'plant1', route: '/' },
      { text: 'plant2', route: '/' }
    ]
  })
}
</script>
<style scoped></style>
