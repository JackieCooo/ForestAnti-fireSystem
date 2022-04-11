<template>
  <el-space direction="vertical" alignment="start" :size="30">
    <el-space :size="20">
      <InfoCard :src="''" title="test" :value="10"></InfoCard>
      <InfoCard :src="''" title="test" :value="10"></InfoCard>
      <InfoCard :src="''" title="test" :value="10"></InfoCard>
    </el-space>
    <el-table :data="data" :cell-style="cellStyle" :row-style="rowStyle" :highlight-current-row="true" :header-row-style="headerRowStyle" :header-cell-style="headerCellStyle">
      <el-table-column label="状态" prop="status" align="center" :width="100">
        <template #default="scope">
          <StatusDot :type="scope.row.status"></StatusDot>
        </template>
      </el-table-column>
      <el-table-column label="序号" prop="no" align="center" :sortable="true" :width="100"></el-table-column>
      <el-table-column label="区域" prop="sector" align="center" :sortable="true" :width="100">
        <template #default="scope">
          {{scope.row.x}}-{{scope.row.y}}
        </template>
      </el-table-column>
      <el-table-column :width="300">
        <template #header>
          <el-input placeholder="搜索序号、区域号" v-model="input"></el-input>
        </template>
        <template #default>
          <el-space>
            <el-button>刷新</el-button>
            <el-button type="warning">维修</el-button>
          </el-space>
        </template>
      </el-table-column>
    </el-table>
  </el-space>
</template>

<script>
import InfoCard from "@/components/InfoCard";
import StatusDot from "@/components/StatusDot";
export default {
  name: "SensorMangePage",
  components: {
    InfoCard,
    StatusDot,
  },
  data() {
    return {
      input: '',
      data: [
        {status: 'online', no: 1, x: 0, y: 0},
        {status: 'offline', no: 2, x: 0, y: 1},
        {status: 'repair', no: 3, x: 0, y: 2},
      ]
    }
  },
  computed: {
    cellStyle() {
      return {
        textAlign: 'center',
        color: 'white',
        fontSize: '15px',
        border: 'none',
      }
    },
    headerRowStyle() {
      return {
        backgroundColor: '#1a1a1a',
        borderBottom: 'none',
      }
    },
    headerCellStyle() {
      return {
        color: 'white',
        fontWeight: 'bold',
        fontSize: '18px',
      }
    }
  },
  methods: {
    rowStyle(row) {
      if (row.rowIndex % 2 === 0) {
        return {
          backgroundColor: '#2a2a2a',
        }
      }
      else {
        return {
          backgroundColor: '#1a1a1a',
        }
      }
    }
  }
}
</script>

<style lang="less" scoped>
:deep(.el-table th, .el-table tr) {
  background-color: transparent;
}
</style>