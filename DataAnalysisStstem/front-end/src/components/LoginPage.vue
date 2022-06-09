<template>
  <div>
    <el-image :src="require('@/assets/LoginBg.jpeg')" fit="contain" class="login-bg"></el-image>
    <el-space direction="vertical" :size="20" class="login-box">
      <h1 class="title">登录</h1>
      <el-input placeholder="请输入用户名" v-model="username" clearable></el-input>
      <el-input placeholder="请输入密码" v-model="password" :show-password="false"></el-input>
      <el-button round type="primary" class="login-btn" @click="login">登录</el-button>
    </el-space>
  </div>
</template>

<script>
export default {
  name: "LoginPage",
  data() {
    return {
      username: '',
      password: '',
    }
  },
  methods: {
    login() {
      this.$store.commit("login", {})
    }
  }
}
</script>

<style lang="less" scoped>
.login-bg {
  width: 100%;
  height: 100%;
  opacity: 0.5;
  filter: brightness(75%);
}

:deep(.el-input__inner) {
  width: 300px;
  height: 45px;
  border-radius: 25px;
  margin-bottom: 10px;
  border: none;
}

.login-btn {
  width: 300px;
  height: 45px;
  border-radius: 25px;
  font-size: 18px;
}

.title {
  color: #303133;
}

.login-box {
  position: absolute;
  top: 150px;
  left: 550px;
  width: 400px;
  height: 400px;
  background-color: white;
  border-radius: 10px;
}
</style>