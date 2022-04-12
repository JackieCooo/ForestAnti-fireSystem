<template>
  <el-space class="box" :size="20">
    <component :is="cardIcon"></component>
    <el-space direction="vertical" :size="0" alignment="start">
      <span class="title">{{title}}</span>
      <span class="value">{{value}}</span>
    </el-space>
  </el-space>
</template>

<script>
const onlineIcon = {
  template: '<div class="iconfont icon-zaixianim"></div>'
}
const offlineIcon = {
  template: '<div class="iconfont icon-lixianim"></div>'
}
const repairIcon = {
  template: '<div class="iconfont icon-weixiu"></div>'
}
export default {
  name: "InfoCard",
  props: {
    type: String,
    title: String,
    value: Number,
  },
  computed: {
    cardIcon() {
      if (this.type === 'online') {
        return onlineIcon
      }
      else if (this.type === 'offline') {
        return offlineIcon
      }
      else if (this.type === 'repair') {
        return repairIcon
      }
      else return {template: ''}
    }
  }
}
</script>

<style lang="less" scoped>
.box {
  width: 240px;
  height: 120px;
  border-radius: 15px;
  background-color: #1a1a1ae6;
}

.el-image {
  width: 50px;
  height: 50px;
  margin-left: 15px;
}

.title {
  color: white;
  font-size: 18px;
  font-weight: bold;
}

.value {
  color: white;
  font-size: 22px;
  font-weight: bold;
}

.iconfont {
  color: white;
  font-size: 50px;
  margin-left: 20px;
}
</style>