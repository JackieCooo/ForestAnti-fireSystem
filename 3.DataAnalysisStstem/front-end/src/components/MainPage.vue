<template>
  <div>
    <el-image :src="require('@/assets/MainBg.jpeg')" fit="contain" class="bg"></el-image>
    <el-container class="container">
      <el-aside>
        <MenuBar></MenuBar>
      </el-aside>
      <el-main>
        <router-view></router-view>
      </el-main>
    </el-container>
  </div>
</template>

<script>
import MenuBar from "@/components/MenuBar";

export default {
  name: "MainPage",
  components: {
    MenuBar,
  }
}
</script>

<style lang="less" scoped>
.container {
  position: absolute;
  left: 0;
  top: 0;
}

.bg {
  width: 100%;
  height: 100%;
  filter: brightness(30%);
}
</style>