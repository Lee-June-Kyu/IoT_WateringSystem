<template>
  <v-app>
    <v-container class="main-cont">
      <div class="plant-info" style="display: flex; flex-direction: row">
        <v-card flat>
          <v-list-item-group>
            <v-list-item>
              <v-list-item-content>
                <v-list-item-subtitle>이름</v-list-item-subtitle>
                <v-list-item-title>선인장</v-list-item-title>
              </v-list-item-content>
            </v-list-item>

            <v-list-item>
              <v-list-item-content>
                <v-list-item-subtitle>종류</v-list-item-subtitle>
                <v-list-item-title>선인장</v-list-item-title>
              </v-list-item-content>
            </v-list-item>

            <v-list-item>
              <v-list-item-content>
                <v-list-item-subtitle>기기번호</v-list-item-subtitle>
                <v-list-item-title>0000</v-list-item-title>
              </v-list-item-content>
            </v-list-item>

            <v-list-item>
              <v-list-item-content>
                <v-list-item-subtitle>키우기 시작한 날짜</v-list-item-subtitle>
                <v-list-item-title>2022-11-16</v-list-item-title>
              </v-list-item-content>
            </v-list-item>

            <v-list-item>
              <v-list-item-content>
                <v-list-item-subtitle>마지막 물 준 날짜</v-list-item-subtitle>
                <v-list-item-title>2022-11-16</v-list-item-title>
              </v-list-item-content>
            </v-list-item>

            <v-list-item>
              <v-list-item-content>
                <v-list-item-subtitle>기타</v-list-item-subtitle>
                <v-list-item-title>......</v-list-item-title>
              </v-list-item-content>
            </v-list-item>
          </v-list-item-group>
        </v-card>
        <v-spacer></v-spacer>
        <v-card flat style="display: flex; flex-direction: column">
          <div style="">
            <v-spacer></v-spacer>
            <v-btn small style="float: right"> 물 주기</v-btn>
          </div>
          <v-spacer></v-spacer>
          <div style="margin-right: 300px">
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
          <div>
            <v-btn small> 측정 </v-btn>
          </div>
        </v-card-title>
        <LineChart />
      </div>
    </v-container>
  </v-app>
</template>

<script>
import LineChart from '../components/LineChart.vue'
export default {
  name: 'Main',
  components: {
    LineChart
  },
  data() {
    return {}
  },
  async created() {}
}
</script>
<style scoped>
.main-cont {
  padding-top: 30px;
}
.text-caption {
  font-size: 13px;
  margin-top: 17px;
}
</style>
