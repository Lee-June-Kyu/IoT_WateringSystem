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
    style="font-family: 'Jua', sans-serif !important"
  />
</template>

<script>
import { Line as LineChartGenerator } from 'vue-chartjs/legacy' // legacy
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
            data: [0],
            font: {
              family: "'Jua'"
            }
          }
        ],
        options: {
          responsive: false,
          legend: {
            labels: {
              fontColor: 'red',
              fontSize: 18,
              font: {
                family: 'Jua'
              }
            }
          },
          scales: {
            yAxes: [
              {
                ticks: {
                  beginAtZero: true,
                  stepSize: 2,
                  fontColor: 'rgba(251, 203, 9, 1)',
                  fontSize: 14,
                  font: {
                    family: "'Jua'"
                  }
                },
                gridLines: {
                  color: 'rgba(166, 201, 226, 1)',
                  lineWidth: 3
                }
              }
            ],
            xAxes: [
              {
                ticks: {
                  fontColor: 'rgba(12, 13, 13, 1)',
                  fontSize: 14
                },
                gridLines: {
                  color: 'rgba(87, 152, 23, 1)',
                  lineWidth: 1
                }
              }
            ],
            tooltips: {
              bodyFontFamily: 'Jua'
            }
          }
        }
      },

      chartOptions: {
        responsive: true,
        maintainAspectRatio: false
      }
    }
  },
  computed: {},
  watch: {
    $route() {
      this.chartData.labels = []
      this.chartData.datasets[0].data = [0]
      this.GetHumidity()
    }
  },
  async created() {
    await this.GetHumidity()
  },
  methods: {
    async GetHumidity() {
      await axios
        .get(process.env.VUE_APP_API + `/web/humidity/${this.$route.params.id}`)
        .then(res => {
          console.log('#################################')
          console.log(this.$route.path.split('/')[1])
          console.log('원하는 data: ', res)
          // console.log(res.data.data[0].createdAt.slice(0, 10))
          // this.chartData.labels.push(res.data.data[0].createdAt.slice(0, 10))
          // console.log('습도', res.data.data[0].humidity_value)
          // this.chartData.datasets[0].data.push(res.data.data[0].humidity_value)
          console.log(this.chartData)
          let temp = res.data.data

          temp.sort((a, b) => {
            return Date(a.createdAt) - Date(b.createdAt)
          })

          console.log('temp', temp)

          let temp2 = temp.slice(temp.length - 10)
          console.log(temp2)

          for (let i = 1; i < 11; i++) {
            this.chartData.labels.push(temp2[i].createdAt.slice(0, 10))
            this.chartData.datasets[0].data.push(temp2[i].humidity_value)
            console.log(this.chartData)
          }
        })
        .catch(error => {
          console.log('Error: plants', error)
        })
    }
  }
}

// let cv = document.querySelector('canvas')
// var ctx = cv.getContext('2d')
// ctx.default.font.size = '18px '
</script>

<style lang="scss">
@font-face {
  font-family: 'Jua', sans-serif;
}
.v-application .text-caption {
  font-family: 'Jua', sans-serif !important;
}
canvas {
  font-family: 'Jua', sans-serif !important;
}
</style>
