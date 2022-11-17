<template>
  <v-app>
    <v-container class="main-cont">
      <div class="plant-info" style="display: flex; flex-direction: row">
        <v-card width="500">
          <v-list-item-group>
            <v-list-item style="display: flex; flex-direction: row">
              <!-- <div> -->
              <v-list-item-content class="pl-4 pt-4">
                <v-list-item-subtitle>이름</v-list-item-subtitle>
                <v-list-item-title>{{ plantdata.plant_name }}</v-list-item-title>
              </v-list-item-content>
              <!-- </div> -->
              <!-- <div> -->
              <v-list-item-content>
                <v-list-item-subtitle>종류</v-list-item-subtitle>
                <v-list-item-title>{{ plantdata.plant_kind }}</v-list-item-title>
              </v-list-item-content>
              <!-- </div> -->
            </v-list-item>

            <v-divider></v-divider>

            <v-list-item style="display: flex; flex-direction: row">
              <!-- <div> -->
              <v-list-item-content class="pl-4 pt-4">
                <v-list-item-subtitle>키우기 시작한 날짜</v-list-item-subtitle>
                <v-list-item-title>{{ plantdata.starting_date }}</v-list-item-title>
              </v-list-item-content>
              <!-- </div> -->

              <!-- <v-divider vertical></v-divider> -->
              <!-- <div> -->
              <v-list-item-content>
                <v-list-item-subtitle>마지막 물 준 날짜</v-list-item-subtitle>
                <v-list-item-title>{{ plantdata.watering_date }}</v-list-item-title>
              </v-list-item-content>
              <!-- </div> -->
            </v-list-item>

            <v-divider></v-divider>

            <v-list-item class="">
              <!-- <div> -->
              <v-list-item-content class="pl-4 pt-4" style="display: flex; flex-direction: row">
                <v-list-item-subtitle>주기</v-list-item-subtitle>
                <v-list-item-title>{{ plantdata.watering_cycle }}</v-list-item-title>
              </v-list-item-content>
              <!-- </div> -->

              <!-- <v-divider vertical></v-divider> -->
              <!-- <div> -->
              <v-list-item-content>
                <v-list-item-subtitle>기기번호</v-list-item-subtitle>
                <v-list-item-title>{{ plantdata.arduino_url }}</v-list-item-title>
              </v-list-item-content>
              <!-- </div> -->
            </v-list-item>

            <v-divider></v-divider>

            <v-list-item>
              <v-list-item-content class="pl-4 pt-4">
                <v-list-item-subtitle>기타</v-list-item-subtitle>
                <v-list-item-title>{{ plantdata.etc }}</v-list-item-title>
              </v-list-item-content>
            </v-list-item>
          </v-list-item-group>
        </v-card>
        <v-spacer></v-spacer>
        <v-card flat style="display: flex; flex-direction: column">
          <form action="" @submit.prevent="onSubmit">
            <div style="">
              <v-spacer></v-spacer>
              <!-- <v-btn small type="submit" style="float: right"> 물 주기</v-btn> -->
              <v-btn class="mx-2" fab color="#EEF1FF" small type="submit" style="float: right"
                ><v-icon>fas fa-faucet</v-icon></v-btn
              >
            </div>
          </form>
          <v-spacer></v-spacer>

          <div style="margin-right: 370px">
            <v-img max-width="200" max-height="200" src="../assets/flower.png"></v-img>
          </div>
        </v-card>
      </div>
      <div class="h-graph">
        <v-card-title>
          <v-icon color="#B8E8FC" class="mr-3" size="20"> fas fa-droplet </v-icon>
          <div>
            <p class="text-caption">습도</p>
          </div>
          <v-spacer></v-spacer>
          <form action="" @submit.prevent="Measure()">
            <div>
              <v-btn small type="submit"> 측정 </v-btn>
            </div>
          </form>
        </v-card-title>
        <LineChart />
      </div>
    </v-container>
  </v-app>
</template>

<script>
import axios from 'axios'
import LineChart from '../components/LineChart.vue'
export default {
  name: 'Main1',
  components: {
    LineChart
  },
  data() {
    return {
      plantdata: {}
    }
  },
  created() {
    this.GetPlants()
  },
  mount() {
    this.GetPlants()
  },
  methods: {
    async GetPlants() {
      await axios
        .get(process.env.VUE_APP_API + `/web/plant/1`)
        .then(res => {
          this.plantdata = res.data.data
          this.plantdata.starting_date = this.plantdata.starting_date.slice(0, 10)
          this.plantdata.watering_date = this.plantdata.watering_date.slice(0, 10)
        })
        .catch(error => {
          console.log('Error: plants', error)
        })
    },
    async onSubmit() {
      console.log('보내기')
      const axiosBody = {
        number: 1,
        id: this.$route.params.id
      }
      await axios
        .patch(process.env.VUE_APP_API + `/web/watering`, axiosBody)
        .then(() => {
          console.log('보내기 성공')
        })
        .catch(error => {
          console.log('Error: plants', error)
        })
    },
    async Measure() {
      const axiosBody = {
        number: 1,
        id: this.$route.params.id
      }
      await axios
        .patch(process.env.VUE_APP_API + `/web/measure`, axiosBody)
        .then(res => {
          this.plantdata = res.data.data
          this.plantdata.starting_date = this.plantdata.starting_date.slice(0, 10)
          this.plantdata.watering_date = this.plantdata.watering_date.slice(0, 10)
          console.log(this.plantdata)
        })
        .catch(error => {
          console.log('Error: plants', error)
        })
    }
  }
}
</script>
<style scoped>
.main-cont {
  padding-top: 80px;
  font-family: 'Jua', sans-serif;
}
/* .list-item-content-padding {
  padding: 20px;
} */
/* .v-list-item-subtitle {
  font-size: ;
} */
.h-graph {
  padding-top: 45px;
}
.text-caption {
  font-size: 13px;
  margin-top: 17px;
}
</style>
