<template>
  <el-space alignment="start">
    <el-space alignment="start" :size="0" class="center-chart">
      <el-space alignment="start" direction="vertical">
        <el-button circle class="layer-btn">All</el-button>
        <el-button circle class="layer-btn">Temp</el-button>
        <el-button circle class="layer-btn">Humi</el-button>
        <el-button circle class="layer-btn">CO2</el-button>
        <el-button circle class="layer-btn">TPO</el-button>
      </el-space>
      <div class="center" ref="centerChart"></div>
    </el-space>
    <div class="right-top" ref="rightTopChart"></div>
  </el-space>
</template>

<script>
import * as echarts from 'echarts'
import 'echarts/extension/bmap/bmap'
export default {
  name: "FrontPage",
  data() {
    return {

    }
  },
  methods: {
    renderCenterChart() {
      const dom = this.$refs.centerChart
      let chart = echarts.init(dom)
      const data = [
          [0, 0, 0.5, 36, 0.76, 0.20, 255],
          [0, 1, 0.5, 29, 0.56, 0.15, 190],
          [0, 2, 0.5, 36, 0.76, 0.20, 255],
          [0, 3, 0.5, 29, 0.56, 0.15, 190],
          [0, 4, 0.5, 36, 0.76, 0.20, 255],
          [1, 0, 0.5, 29, 0.56, 0.15, 190],
          [1, 1, 0.5, 36, 0.76, 0.20, 255],
          [1, 2, 0.5, 29, 0.56, 0.15, 190],
          [1, 3, 0.5, 36, 0.76, 0.20, 255],
          [1, 4, 0.5, 29, 0.56, 0.15, 190],
          [2, 0, 0.5, 36, 0.76, 0.20, 255],
          [2, 1, 0.5, 29, 0.56, 0.15, 190],
          [2, 2, 0.5, 36, 0.76, 0.20, 255],
          [2, 3, 0.5, 29, 0.56, 0.15, 190],
          [2, 4, 0.5, 36, 0.76, 0.20, 255],
          [3, 0, 0.5, 29, 0.56, 0.15, 190],
          [3, 1, 0.5, 36, 0.76, 0.20, 255],
          [3, 2, 0.5, 29, 0.56, 0.15, 190],
          [3, 3, 0.5, 36, 0.76, 0.20, 255],
          [3, 4, 0.5, 29, 0.56, 0.15, 190],
          [4, 0, 0.5, 36, 0.76, 0.20, 255],
          [4, 1, 0.5, 29, 0.56, 0.15, 190],
          [4, 2, 0.5, 36, 0.76, 0.20, 255],
          [4, 3, 0.5, 29, 0.56, 0.15, 190],
          [4, 4, 0.5, 36, 0.76, 0.20, 255]
      ]
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

      const option = {
        title: {
        },
        tooltip: {
        },
        bmap: {
          center: [113.377868,23.137542],
          zoom: 18,
          roam: true,
          mapStyleV2: {
            styleJson: [{
              "featureType": "land",
              "elementType": "geometry",
              "stylers": {
                "color": "#242f3eff"
              }
            }, {
              "featureType": "manmade",
              "elementType": "geometry",
              "stylers": {
                "color": "#242f3eff"
              }
            }, {
              "featureType": "water",
              "elementType": "geometry",
              "stylers": {
                "color": "#17263cff"
              }
            }, {
              "featureType": "road",
              "elementType": "geometry.fill",
              "stylers": {
                "color": "#9e7d60ff"
              }
            }, {
              "featureType": "road",
              "elementType": "geometry.stroke",
              "stylers": {
                "color": "#554631ff"
              }
            }, {
              "featureType": "districtlabel",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#d69563ff"
              }
            }, {
              "featureType": "districtlabel",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#17263cff",
                "weight": 3
              }
            }, {
              "featureType": "poilabel",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#d69563ff"
              }
            }, {
              "featureType": "poilabel",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#17263cff",
                "weight": 3
              }
            }, {
              "featureType": "subway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "railway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "poilabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "subwaylabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "subwaylabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "tertiarywaysign",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "tertiarywaysign",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "provincialwaysign",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "provincialwaysign",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "nationalwaysign",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "nationalwaysign",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "highwaysign",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "highwaysign",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "green",
              "elementType": "geometry",
              "stylers": {
                "color": "#263b3eff"
              }
            }, {
              "featureType": "nationalwaysign",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#d0021bff"
              }
            }, {
              "featureType": "nationalwaysign",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#ffffffff"
              }
            }, {
              "featureType": "city",
              "elementType": "labels",
              "stylers": {
                "visibility": "on"
              }
            }, {
              "featureType": "city",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "city",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#d69563ff"
              }
            }, {
              "featureType": "city",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#17263cff"
              }
            }, {
              "featureType": "water",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#d69563ff"
              }
            }, {
              "featureType": "water",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#242f3eff"
              }
            }, {
              "featureType": "local",
              "elementType": "geometry.fill",
              "stylers": {
                "color": "#38414eff"
              }
            }, {
              "featureType": "local",
              "elementType": "geometry.stroke",
              "stylers": {
                "color": "#ffffff00"
              }
            }, {
              "featureType": "fourlevelway",
              "elementType": "geometry.fill",
              "stylers": {
                "color": "#38414eff"
              }
            }, {
              "featureType": "fourlevelway",
              "elementType": "geometry.stroke",
              "stylers": {
                "color": "#ffffff00"
              }
            }, {
              "featureType": "tertiaryway",
              "elementType": "geometry.fill",
              "stylers": {
                "color": "#38414eff"
              }
            }, {
              "featureType": "tertiaryway",
              "elementType": "geometry.stroke",
              "stylers": {
                "color": "#ffffff00"
              }
            }, {
              "featureType": "tertiaryway",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#759879ff"
              }
            }, {
              "featureType": "fourlevelway",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#759879ff"
              }
            }, {
              "featureType": "highway",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#759879ff"
              }
            }, {
              "featureType": "highway",
              "elementType": "geometry.fill",
              "stylers": {
                "color": "#9e7d60ff"
              }
            }, {
              "featureType": "highway",
              "elementType": "geometry.stroke",
              "stylers": {
                "color": "#554631ff"
              }
            }, {
              "featureType": "provincialway",
              "elementType": "geometry.fill",
              "stylers": {
                "color": "#9e7d60ff"
              }
            }, {
              "featureType": "provincialway",
              "elementType": "geometry.stroke",
              "stylers": {
                "color": "#554631ff"
              }
            }, {
              "featureType": "tertiaryway",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#1a2e1cff"
              }
            }, {
              "featureType": "fourlevelway",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#1a2e1cff"
              }
            }, {
              "featureType": "highway",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#1a2e1cff"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#1a2e1cff"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#759879ff"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "geometry.fill",
              "stylers": {
                "color": "#9e7d60ff"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "geometry.stroke",
              "stylers": {
                "color": "#554631ff"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "geometry.fill",
              "stylers": {
                "color": "#9e7d60ff"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "geometry.stroke",
              "stylers": {
                "color": "#554631ff"
              }
            }, {
              "featureType": "arterial",
              "elementType": "geometry.fill",
              "stylers": {
                "color": "#9e7d60ff"
              }
            }, {
              "featureType": "arterial",
              "elementType": "geometry.stroke",
              "stylers": {
                "color": "#554631fa"
              }
            }, {
              "featureType": "medicallabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "medicallabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "entertainmentlabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "entertainmentlabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "estatelabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "estatelabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "businesstowerlabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "businesstowerlabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "companylabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "companylabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "governmentlabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "governmentlabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "restaurantlabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "restaurantlabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "hotellabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "hotellabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "shoppinglabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "shoppinglabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "lifeservicelabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "lifeservicelabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "carservicelabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "carservicelabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "financelabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "financelabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "otherlabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "otherlabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "airportlabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "on"
              }
            }, {
              "featureType": "airportlabel",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#d69563ff"
              }
            }, {
              "featureType": "airportlabel",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#17263cff"
              }
            }, {
              "featureType": "airportlabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "highway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "6"
              }
            }, {
              "featureType": "highway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "7"
              }
            }, {
              "featureType": "highway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "8"
              }
            }, {
              "featureType": "highway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "9"
              }
            }, {
              "featureType": "highway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "10"
              }
            }, {
              "featureType": "highway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "6"
              }
            }, {
              "featureType": "highway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "7"
              }
            }, {
              "featureType": "highway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "8"
              }
            }, {
              "featureType": "highway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "9"
              }
            }, {
              "featureType": "highway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "10"
              }
            }, {
              "featureType": "nationalway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "6"
              }
            }, {
              "featureType": "nationalway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "7"
              }
            }, {
              "featureType": "nationalway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "8"
              }
            }, {
              "featureType": "nationalway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "9"
              }
            }, {
              "featureType": "nationalway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "10"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "6"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "7"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "8"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "9"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "10"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "6"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "7"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "8"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "9"
              }
            }, {
              "featureType": "nationalway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "10"
              }
            }, {
              "featureType": "highway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "6"
              }
            }, {
              "featureType": "highway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "7"
              }
            }, {
              "featureType": "highway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "8"
              }
            }, {
              "featureType": "highway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "9"
              }
            }, {
              "featureType": "highway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "10"
              }
            }, {
              "featureType": "provincialway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "8,9",
                "level": "8"
              }
            }, {
              "featureType": "provincialway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "8,9",
                "level": "9"
              }
            }, {
              "featureType": "provincialway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "8,9",
                "level": "8"
              }
            }, {
              "featureType": "provincialway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "8,9",
                "level": "9"
              }
            }, {
              "featureType": "provincialway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "8,9",
                "level": "8"
              }
            }, {
              "featureType": "provincialway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "8,9",
                "level": "9"
              }
            }, {
              "featureType": "cityhighway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "6"
              }
            }, {
              "featureType": "cityhighway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "7"
              }
            }, {
              "featureType": "cityhighway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "8"
              }
            }, {
              "featureType": "cityhighway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "9"
              }
            }, {
              "featureType": "cityhighway",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "10"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "6"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "7"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "8"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "9"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "10"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "6"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "7"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "8"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "9"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "6,10",
                "level": "10"
              }
            }, {
              "featureType": "arterial",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "9,10",
                "level": "9"
              }
            }, {
              "featureType": "arterial",
              "stylers": {
                "curZoomRegionId": "0",
                "curZoomRegion": "9,10",
                "level": "10"
              }
            }, {
              "featureType": "arterial",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "9,10",
                "level": "9"
              }
            }, {
              "featureType": "arterial",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "9,10",
                "level": "10"
              }
            }, {
              "featureType": "arterial",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "9,10",
                "level": "9"
              }
            }, {
              "featureType": "arterial",
              "elementType": "labels",
              "stylers": {
                "visibility": "off",
                "curZoomRegionId": "0",
                "curZoomRegion": "9,10",
                "level": "10"
              }
            }, {
              "featureType": "building",
              "elementType": "geometry.topfill",
              "stylers": {
                "color": "#2a3341ff"
              }
            }, {
              "featureType": "building",
              "elementType": "geometry.sidefill",
              "stylers": {
                "color": "#313b4cff"
              }
            }, {
              "featureType": "building",
              "elementType": "geometry.stroke",
              "stylers": {
                "color": "#1a212eff"
              }
            }, {
              "featureType": "road",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#759879ff"
              }
            }, {
              "featureType": "road",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#1a2e1cff"
              }
            }, {
              "featureType": "provincialway",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#759879ff"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#759879ff"
              }
            }, {
              "featureType": "arterial",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#759879ff"
              }
            }, {
              "featureType": "provincialway",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#1a2e1cff"
              }
            }, {
              "featureType": "cityhighway",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#1a2e1cff"
              }
            }, {
              "featureType": "arterial",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#1a2e1cff"
              }
            }, {
              "featureType": "local",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "manmade",
              "elementType": "labels.text.fill",
              "stylers": {
                "color": "#d69563ff"
              }
            }, {
              "featureType": "manmade",
              "elementType": "labels.text.stroke",
              "stylers": {
                "color": "#17263cff"
              }
            }, {
              "featureType": "subwaystation",
              "elementType": "geometry",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "transportationlabel",
              "elementType": "labels.icon",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "transportationlabel",
              "elementType": "labels",
              "stylers": {
                "visibility": "off"
              }
            }, {
              "featureType": "estate",
              "elementType": "geometry",
              "stylers": {
                "color": "#2a3341ff"
              }
            }]
          },
        },
        visualMap: {
          type: 'continuous',
          min: 0,
          max: 100,
          dimension: 2, // 映射series.data里面的第2元素
          seriesIndex: 0, // 映射第1个series
          inRange: {
            // 选中范围中的视觉配置
            color: ['green', 'yellow', 'orange', 'red'], //  定义了图形颜色映射的颜色列表
            symbolSize: [0, 100], //  定义了图形尺寸的映射范围
            opacity: 0.5,
          },
          show: false,
        },
        series: [
          {
            type: 'custom',
            coordinateSystem: 'bmap',
            renderItem: renderItem,
            animation: false,
            encode: {
              tooltip: [2, 3, 4, 5, 6],
            },
            data: data,
            tooltip: {
            },
          }
        ]
      }
      chart.setOption(option)
    },
    renderRightTopChart() {
      const dom = this.$refs.rightTopChart
      let chart = echarts.init(dom, 'dark')

      const option = {
        title: {
          text: '测试',
        },
        tooltip: {},
        dataSet: {
          dimensions: [
            {}
          ],
          source: [
            {x: 113.375859, y: 23.138548, overall: 10},
            {x: 113.379686, y: 23.141539, overall: 20},
            {x: 113.384698, y: 23.137751, overall: 30},
            {x: 113.380135, y: 23.137618, overall: 40},
          ]
        },

      }
    }
  },
  mounted() {
    this.renderCenterChart()
  },
}
</script>

<style lang="less" scoped>
.center {
  width: 800px;
  height: 600px;
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

.center-chart {
  background-color: #242f3eff;
}
</style>