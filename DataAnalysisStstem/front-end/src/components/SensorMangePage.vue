<template>
  <el-space direction="vertical" alignment="start" :size="30">
    <el-space :size="20">
      <InfoCard type="online" title="在线" :value="10"></InfoCard>
      <InfoCard type="offline" title="维修中" :value="10"></InfoCard>
      <InfoCard type="repair" title="离线" :value="10"></InfoCard>
    </el-space>
    <el-table :data="filterTableData" :cell-style="cellStyle" :row-style="rowStyle" :highlight-current-row="false" :header-row-style="headerRowStyle" :header-cell-style="headerCellStyle" :max-height="700">
      <el-table-column label="状态" prop="status" align="center" :width="100">
        <template #default="scope">
          <StatusDot :type="scope.row.status"></StatusDot>
        </template>
      </el-table-column>
      <el-table-column label="序号" prop="no" align="center" :sortable="true" :width="150"></el-table-column>
      <el-table-column label="区域" prop="sector" align="center" :sortable="true" :width="150">
        <template #default="scope">
          {{scope.row.x}}-{{scope.row.y}}
        </template>
      </el-table-column>
      <el-table-column :width="360">
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
    // 定制表格单元格样式
    cellStyle() {
      return {
        textAlign: 'center',
        color: 'white',
        fontSize: '15px',
        border: 'none',
      }
    },
    // 定制表格表头样式
    headerRowStyle() {
      return {
        backgroundColor: '#1a1a1a',
        border: 'none',
      }
    },
    // 定制表格表头单元格样式
    headerCellStyle() {
      return {
        color: 'white',
        fontWeight: 'bold',
        fontSize: '18px',
        border: 'none',
      }
    },
    // 根据搜索框内容过滤显示数据
    filterTableData() {
      return this.data.filter((data) => !this.input || data.no.toString().includes(this.input) || data.x.toString().includes(this.input) || data.y.toString().includes(this.input))
    },
  },
  methods: {
    // 定制表格行样式
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
:deep(.el-table th, .el-table tr, .el-table td) {
  background-color: transparent;
}

:deep(.el-table tbody tr:hover>td) {
  background: none !important;
}

:deep(.el-table__inner-wrapper::before) {
  left:0;
  top:0;
  width:100%;
  height:0;
  z-index:3;
}

.el-table {
  border-radius: 10px;
  background-color: #2a2a2a;
  opacity: 0.9;
}

:deep(.el-input__inner) {
  background-color: #2a2a2a;
  border: none;
  box-shadow: none;
  color: white;
}

</style>