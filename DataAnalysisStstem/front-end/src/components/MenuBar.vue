<template>
  <div class="container">
    <el-menu>
      <el-menu-item index="home" @click="gotoPage">首页</el-menu-item>
      <el-menu-item index="sensor" @click="gotoPage">传感器管理</el-menu-item>
      <el-menu-item index="drone" @click="gotoPage">无人机管理</el-menu-item>
      <el-menu-item index="setting" @click="gotoPage">系统设置</el-menu-item>
    </el-menu>
    <el-button type="text" class="logout-btn" @click="logout">登出</el-button>
  </div>
</template>

<script>
export default {
  name: "MenuBar",
  methods: {
    gotoPage(e) {
      console.log(e.index)
      if (e.index === 'home') this.$router.push('/home')
      else this.$router.push('/home/' + e.index)
    },
    logout() {
      this.$store.commit("logout")
      this.$router.push("/login")
    }
  }
}
</script>

<style lang="less" scoped>
.container {
  margin-top: 15px;
  margin-left: 15px;
  background-color: #2a2a2a;
  opacity: 0.9;
}

.el-menu {
  width: 150px;
  height: 640px;
  background-color: #2a2a2a;
  border: none;
}

.el-menu-item {
  color: white;
}

.el-menu-item:hover {
  background-color: #1a1a1a;
}

.logout-btn {
  padding-bottom: 20px;
  height: 50px;
  width: 150px;
  color: white;
  font-weight: bold;
  font-size: 20px;
}
</style>