<template>
  <div class="container">
    <el-menu>
      <el-menu-item>首页</el-menu-item>
      <el-menu-item>传感器管理</el-menu-item>
      <el-menu-item>无人机管理</el-menu-item>
      <el-menu-item>系统设置</el-menu-item>
    </el-menu>
  </div>
</template>

<script>
export default {
  name: "MenuBar"
}
</script>

<style lang="less" scoped>
.container {
  margin-top: 10px;
  margin-left: 10px;
  background-color: #303133;
  opacity: 0.8;
}

.el-menu {
  width: 150px;
  height: 700px;
  background-color: #303133;
  border: none;
}

.el-menu-item {
  color: white;
}

.el-menu-item:hover {
  background-color: #1e1e1e;
}
</style>