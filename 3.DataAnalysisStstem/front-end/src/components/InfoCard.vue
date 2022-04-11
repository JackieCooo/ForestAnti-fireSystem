<template>
  <el-space class="box" :size="20">
    <el-image :src="src" fit="fill"></el-image>
    <el-space direction="vertical" :size="0" alignment="start">
      <span class="title">{{title}}</span>
      <span class="value">{{value}}</span>
    </el-space>
  </el-space>
</template>

<script>
export default {
  name: "InfoCard",
  props: {
    src: String,
    title: String,
    value: Number,
  }
}
</script>

<style lang="less" scoped>
.box {
  width: 240px;
  height: 120px;
  border-radius: 15px;
  background-color: #242f3ee6;
}

.el-image {
  width: 50px;
  height: 50px;
  margin-left: 15px;
}

.title, .value {
  color: white;
  font-size: 20px;
  font-weight: bold;
}
</style>