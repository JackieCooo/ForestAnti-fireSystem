<template>
  <div :style="dotStyle"></div>
</template>

<script>
export default {
  name: "StatusDot",
  props: {
    type: String,
  },
  computed: {
    dotStyle() {
      let style = {
        width: '10px',
        height: '10px',
        borderRadius: '5px',
        backgroundColor: null
      }
      switch (this.type) {
        case 'online':
          style.backgroundColor = '#67C23A'
          break
        case 'offline':
          style.backgroundColor = '#F56C6C'
          break
        case 'repair':
          style.backgroundColor = '#E6A23C'
          break
      }
      return style
    }
  }
}
</script>

<style lang="less" scoped>

</style>