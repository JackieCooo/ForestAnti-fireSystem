<template>
  <el-space>
    <div class="left" ref="leftChart"></div>
    <div class="center" ref="centerChart"></div>
  </el-space>
</template>

<script>
import * as echarts from 'echarts'
import 'echarts/extension/bmap/bmap'
export default {
  name: "FrontPage",
  methods: {
    renderLeftChart() {
      const dom = this.$refs.leftChart
      let chart = echarts.init(dom, 'dark')
      chart.setOption({
        title: {
          text: 'echart测试',
          left: 'center',
          top: 10,
        },
        xAxis: {
          data: ['衬衫', '羊毛衫', '雪纺衫', '裤子', '高跟鞋', '袜子']
        },
        yAxis: {},
        series: [
          {
            name: '销量',
            type: 'bar',
            data: [5, 20, 36, 10, 10, 20],
          },
        ],
        tooltip: {},
        backgroundColor: 'rgba(48, 49, 51, 0.8)',
      })
    },
    renderCenterChart() {
      const dom = this.$refs.centerChart
      let chart = echarts.init(dom)
      chart.setOption({

      })
    }
  },
  mounted() {
    this.renderLeftChart()
  },
}
</script>

<style lang="less" scoped>
.center {
  width: 600px;
  height: 400px;
  color: white;
}
</style>