<template>
  <LineChartGenerator
    :chart-options="chartOptions"
    :chart-data="chartData"
    :chart-id="chartId"
    :dataset-id-key="datasetIdKey"
    :plugins="plugins"
    :css-classes="cssClasses"
    :styles="styles"
    :width="width"
    :height="height"
  />
</template>

<script>
import { Line as LineChartGenerator } from 'vue-chartjs' // legacy
import axios from 'axios'

import {
  Chart as ChartJS,
  Title,
  Tooltip,
  Legend,
  LineElement,
  LinearScale,
  CategoryScale,
  PointElement
} from 'chart.js'

ChartJS.register(Title, Tooltip, Legend, LineElement, LinearScale, CategoryScale, PointElement)

export default {
  name: 'LineChart',
  components: {
    LineChartGenerator
  },
  props: {
    chartId: {
      type: String,
      default: 'line-chart'
    },
    datasetIdKey: {
      type: String,
      default: 'data'
    },
    width: {
      type: Number,
      default: 400
    },
    height: {
      type: Number,
      default: 200
    },
    cssClasses: {
      default: '',
      type: String
    },
    styles: {
      type: Object,
      default: () => {}
    },
    plugins: {
      type: Array,
      default: () => []
    }
  },
  data() {
    return {
      chartData: {
        labels: [0],
        datasets: [
          {
            label: '퍼센트(%)',
            backgroundColor: '#BCE29E',
            data: [0]
          }
        ]
      },
      chartOptions: {
        responsive: true,
        maintainAspectRatio: false
      }
    }
  },
  async created() {
    await this.GetHumidity()
  },
  methods: {
    async GetHumidity() {
      await axios
        .get(process.env.VUE_APP_API + `/web/humidity/${this.$route.path.split('/')[1]}`)
        .then(res => {
          console.log('#################################')
          console.log(this.$route.path.split('/')[1])
          console.log('원하는 data: ', res)
          // console.log(res.data.data[0].createdAt.slice(0, 10))
          // this.chartData.labels.push(res.data.data[0].createdAt.slice(0, 10))
          // console.log('습도', res.data.data[0].humidity_value)
          // this.chartData.datasets[0].data.push(res.data.data[0].humidity_value)
          console.log(this.chartData)
          for (let i = 1; i < 11; i++) {
            this.chartData.labels.push(res.data.data[i].createdAt.slice(0, 10))
            this.chartData.datasets[0].data.push(res.data.data[i].humidity_value)
            console.log(this.chartData)
          }
        })
        .catch(error => {
          console.log('Error: plants', error)
        })
    }
  }
}
</script>
<style>
* {
  font-family: 'Jua', sans-serif;
}
</style>
