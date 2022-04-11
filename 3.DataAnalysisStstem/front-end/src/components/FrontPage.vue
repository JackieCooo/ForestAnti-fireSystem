<template>
  <el-space alignment="start" :size="15">
    <el-space alignment="start" :size="0" class="center-chart">
      <el-space alignment="start" direction="vertical">
        <el-button circle class="layer-btn" @click="renderCenterChart(0)">All</el-button>
        <el-button circle class="layer-btn" @click="renderCenterChart(1)">Temp</el-button>
        <el-button circle class="layer-btn" @click="renderCenterChart(2)">Huma</el-button>
        <el-button circle class="layer-btn" @click="renderCenterChart(3)">CO2</el-button>
        <el-button circle class="layer-btn" @click="renderCenterChart(4)">TPO</el-button>
      </el-space>
      <div class="center" ref="centerChart"></div>
    </el-space>
    <el-space direction="vertical" alignment="start" :size="15">
      <div class="right-top" ref="rightTopChart"></div>
      <div class="right-bottom" ref="rightBottomChart"></div>
    </el-space>
  </el-space>
</template>

<script>
import * as echarts from 'echarts'
import 'echarts/extension/bmap/bmap'

let centerChart = null
let rightTopChart = null
let rightBottomChart = null

export default {
  name: "FrontPage",
  data() {
    return {
      data: [
        [0, 0, 0.5, 36, 0.76, 0.20, 255],
        [0, 1, 0.3, 29, 0.56, 0.15, 190],
        [0, 2, 0.5, 36, 0.76, 0.20, 255],
        [0, 3, 0.2, 29, 0.56, 0.15, 190],
        [0, 4, 0.5, 36, 0.76, 0.20, 255],
        [1, 0, 0.5, 29, 0.56, 0.15, 190],
        [1, 1, 0.4, 36, 0.76, 0.20, 255],
        [1, 2, 0.5, 29, 0.56, 0.15, 190],
        [1, 3, 0.5, 36, 0.76, 0.20, 255],
        [1, 4, 0.5, 29, 0.56, 0.15, 190],
        [2, 0, 0.5, 36, 0.76, 0.20, 255],
        [2, 1, 0.5, 29, 0.56, 0.15, 190],
        [2, 2, 0.5, 36, 0.76, 0.20, 255],
        [2, 3, 0.9, 29, 0.56, 0.15, 190],
        [2, 4, 0.5, 36, 0.76, 0.20, 255],
        [3, 0, 0.5, 29, 0.56, 0.15, 190],
        [3, 1, 0.5, 36, 0.76, 0.20, 255],
        [3, 2, 0.5, 29, 0.56, 0.15, 190],
        [3, 3, 0.5, 36, 0.76, 0.20, 255],
        [3, 4, 0.7, 29, 0.56, 0.15, 190],
        [4, 0, 0.5, 36, 0.76, 0.20, 255],
        [4, 1, 0.5, 29, 0.56, 0.15, 190],
        [4, 2, 0.5, 36, 0.76, 0.20, 255],
        [4, 3, 0.1, 29, 0.56, 0.15, 190],
        [4, 4, 0.5, 36, 0.76, 0.20, 255]
      ]
    }
  },
  methods: {
    renderCenterChart(n) {
      const option = this.setupOption(n)
      centerChart.setOption(option, {replaceMerge: ['visualMap', 'series']})
    },
    getVisualMap(n) {
      // 除温度、总颗粒物外都使用默认配置
      let visualMap = {
        type: 'continuous',
        min: 0,
        max: 1,
        dimension: n+2, // 映射series.data里面的对应元素
        seriesIndex: 0, // 映射第1个series
        inRange: {
          // 选中范围中的视觉配置
          color: ['green', 'yellow', 'orange', 'red'], //  定义了图形颜色映射的颜色列表
          symbolSize: [0, 1], //  定义了图形尺寸的映射范围
          opacity: [0.1, 0.7],  // 定义映射不透明度范围
        },
        show: false,
        precision: 2,  // 精确到小数点后2位
      }

      if (n === 1) {  // 温度
        visualMap.min = -50
        visualMap.max = 150
        visualMap.inRange.symbolSize = [0, 70]
        visualMap.precision = 0
      }
      else if (n === 4) {  // 总颗粒物
        visualMap.min = 0
        visualMap.max = 1000
        visualMap.inRange.symbolSize = [0, 1000]
        visualMap.precision = 0
      }

      return visualMap
    },
    getTooltipFormatter(n) {
      switch (n) {
        case 0:
          return function (params) {
            let s = `<div>`
            s += `<span style="font-weight: bold; font-size: 15px; line-height: 2;">区域 ${params.value[0]}-${params.value[1]}</br></span>`
            s += `<span style="line-height: 2;">火灾几率: ${params.value[2] * 100}%</br></span>`
            s += `<span style="line-height: 2;">温度: ${params.value[3]}℃</br></span>`
            s += `<span style="line-height: 2;">湿度: ${params.value[4] * 100}%</br></span>`
            s += `<span style="line-height: 2;">CO2浓度: ${params.value[5] * 100}%</br></span>`
            s += `<span style="line-height: 2;">总颗粒物: ${params.value[6]}</br></span>`
            s += `</div>`
            return s
          }
        case 1:
          return function (params) {
            let s = `<div>`
            s += `<span style="font-weight: bold; font-size: 15px; line-height: 2;">区域 ${params.value[0]}-${params.value[1]}</br></span>`
            s += `<span style="line-height: 2;">温度: ${params.value[3]}℃</br></span>`
            s += `</div>`
            return s
          }
        case 2:
          return function (params) {
            let s = `<div>`
            s += `<span style="font-weight: bold; font-size: 15px; line-height: 2;">区域 ${params.value[0]}-${params.value[1]}</br></span>`
            s += `<span style="line-height: 2;">湿度: ${params.value[4] * 100}%</br></span>`
            s += `</div>`
            return s
          }
        case 3:
          return function (params) {
            let s = `<div>`
            s += `<span style="font-weight: bold; font-size: 15px; line-height: 2;">区域 ${params.value[0]}-${params.value[1]}</br></span>`
            s += `<span style="line-height: 2;">CO2浓度: ${params.value[5] * 100}%</br></span>`
            s += `</div>`
            return s
          }
        case 4:
          return function (params) {
            let s = `<div>`
            s += `<span style="font-weight: bold; font-size: 15px; line-height: 2;">区域 ${params.value[0]}-${params.value[1]}</br></span>`
            s += `<span style="line-height: 2;">总颗粒物: ${params.value[6]}</br></span>`
            s += `</div>`
            return s
          }
      }
    },
    setupOption(n) {
      const cellCount = [5, 5]  // 区域矩形大小
      const latExtent = [113.376108, 113.38033]  // 区域左右边界经度
      const lngExtent = [23.135381, 23.139967]  // 区域上下边界纬度
      const cellSizeCoord = [  // 每个区域对应的大小
        (lngExtent[1] - lngExtent[0]) / cellCount[0],
        (latExtent[1] - latExtent[0]) / cellCount[1]
      ];
      // 自定义渲染函数
      function renderItem(params, api) {
        const lngIndex = api.value(0)
        const latIndex = api.value(1)
        const pointLeftTop = getCoord(params, api, lngIndex, latIndex)
        const pointRightBottom = getCoord(params, api, lngIndex + 1, latIndex + 1)
        return {
          type: 'rect',
          shape: {
            x: pointLeftTop[0],
            y: pointLeftTop[1],
            width: pointRightBottom[0] - pointLeftTop[0],
            height: pointRightBottom[1] - pointLeftTop[1]
          },
          style: api.style({
            stroke: 'rgba(0,0,0,0.1)'
          }),
          styleEmphasis: api.styleEmphasis()
        };
      }
      // 坐标转换函数
      function getCoord(params, api, lngIndex, latIndex) {
        const coords = params.context.coords || (params.context.coords = [])
        const key = lngIndex + '-' + latIndex
        // bmap returns point in integer, which makes cell width unstable.
        // So we have to use right bottom point.
        return (
            coords[key] ||
            (coords[key] = api.coord([
              +(latExtent[0] + lngIndex * cellSizeCoord[0]).toFixed(6),
              +(lngExtent[0] + latIndex * cellSizeCoord[1]).toFixed(6)
            ]))
        );
      }

      let option = {
        title: {
        },
        tooltip: {
        },
        bmap: {  // 百度地图拓展
          center: [113.377868,23.137542],
          zoom: 18,
          roam: true,
          mapStyleV2: {
            styleId: 'ef8656fb497f13f3911a1a855e6f98fa'
          }
        },
        visualMap: null,
        series: [  // 系列
          {
            type: 'custom',
            coordinateSystem: 'bmap',
            renderItem: renderItem,
            animation: true,
            encode: {
              tooltip: [0, 1, 2, 3, 4, 5, 6],
            },
            data: this.data,
            dimensions: [
              {name: 'x', type: 'number'},
              {name: 'y', type: 'number'},
              {name: 'overall', type: 'float'},
              {name: 'temperature', type: 'number'},
              {name: 'humanity', type: 'float'},
              {name: 'co2', type: 'float'},
              {name: 'tpo', type: 'number'},
            ],
            tooltip: {
              formatter: null,
            }
          }
        ]
      }
      option.visualMap = this.getVisualMap(n)
      option.series[0].tooltip.formatter = this.getTooltipFormatter(n)

      return option
    },
    initCenterChart() {
      const dom = this.$refs.centerChart
      centerChart = echarts.init(dom)
      const option = this.setupOption(0)
      centerChart.setOption(option)
    },
    initRightTopChart() {
      const dom = this.$refs.rightTopChart
      rightTopChart = echarts.init(dom, 'dark')

      const option = {
        title: {
          text: '传感器',
          left: 'center',
          top: 20,
        },
        backgroundColor: '#242f3ecc',
        series: [
          {
            type: 'gauge',
            radius: '50%',
            startAngle: '180',
            endAngle: '360',
            min: 0,
            max: 100,
            axisLine: {
              show: true,
              roundCap: true,
              lineStyle: {
                width: 15,
              }
            },
            splitLine: {
              show: false,
            },
            axisTick: {
              show: false,
            },
            axisLabel: {
              show: false,
            },
            pointer: {
              show: false,
            },
            anchor: {
              show: false,
            },
            progress: {
              show: true,
              roundCap: true,
              width: 15,
              clip: true,
            },
            detail: {
              show: true,
              offsetCenter: [0, '-10%'],
              formatter: function (value) {
                return value + ' 在线'
              },
              fontSize: 20,
              color: '#67C23A',
            },
            data: [70],
          }
        ]
      }

      rightTopChart.setOption(option)
    },
    initRightBottomChart() {
      const dom = this.$refs.rightBottomChart
      rightBottomChart = echarts.init(dom, 'dark')

      const option = {
        title: {
          text: '无人机',
          left: 'center',
          top: 20,
        },
        backgroundColor: '#242f3ecc',
        series: [
          {
            type: 'gauge',
            radius: '50%',
            startAngle: '180',
            endAngle: '360',
            min: 0,
            max: 10,
            axisLine: {
              show: true,
              roundCap: true,
              lineStyle: {
                width: 15,
              }
            },
            splitLine: {
              show: false,
            },
            axisTick: {
              show: false,
            },
            axisLabel: {
              show: false,
            },
            pointer: {
              show: false,
            },
            anchor: {
              show: false,
            },
            progress: {
              show: true,
              roundCap: true,
              width: 15,
              clip: true,
            },
            detail: {
              show: true,
              offsetCenter: [0, '-10%'],
              formatter: function (value) {
                return value + ' 在线'
              },
              fontSize: 20,
              color: '#67C23A',
            },
            data: [8],
          }
        ]
      }

      rightBottomChart.setOption(option)
    }
  },
  mounted() {
    this.initCenterChart()
    this.initRightTopChart()
    this.initRightBottomChart()
  },
}
</script>

<style lang="less" scoped>
.center {
  width: 900px;
  height: 690px;
  color: white;
}

.layer-btn {
  width: 50px;
  height: 50px;
  background: none;
  margin-left: 10px;
  margin-right: 10px;
  margin-top: 15px;
  color: white;
  border-color: white;
}

.layer-btn:hover {
  background-color: white;
  color: #242f3eff;
}

.center-chart {
  background-color: #242f3ecc;
}

.right-top, .right-bottom {
  width: 300px;
  height: 300px;
}
</style>