## **数据包格式**  
数据包分为三段，分别是帧头、数据端、帧尾，其中数据端是可变长度的，根据要返回的数据决定。
### 帧头 （5 Byte）
<table>
    <tr>
        <th>字节</th>
        <th>默认值</th>
        <th>描述</th>
    </tr>
    <tr>
        <td>3</td>
        <td>0xAA</td>
        <td>前导字符</td>
    </tr>
    <tr>
        <td>1</td>
        <td>XX</td>
        <td>
            数据包类型<br />
            0x01: 传感器数据<br />
            0x02: 传感器KeepAlive<br />
            0x03: 无人机KeepAlive<br />
        </td>
    </tr>
    <tr>
        <td>1</td>
        <td>XX</td>
        <td>数据包总长</td>
    </tr>
</table>

### 数据段  （传感器数据）

<table>
    <tr>
        <th>字节</th>
        <th>默认值</th>
        <th>描述</th>
    </tr>
    <tr>
        <td>1</td>
        <td>XX</td>
        <td>温度整数</td>
    </tr>
    <tr>
        <td>1</td>
        <td>XX</td>
        <td>温度小数</td>
    </tr>
    <tr>
        <td>1</td>
        <td>XX</td>
        <td>湿度整数</td>
    </tr>
    <tr>
        <td>1</td>
        <td>XX</td>
        <td>湿度小数</td>
    </tr>
    <tr>
        <td rowspan="2">2</td>
        <td>XX</td>
        <td rowspan="2">CO2含量</td>
    </tr>
    <tr>
        <td>XX</td>
    </tr>
    <tr>
        <td rowspan="2">2</td>
        <td>XX</td>
        <td rowspan="2">CO含量</td>
    </tr>
    <tr>
        <td>XX</td>
    </tr>
    <tr>
        <td rowspan="2">2</td>
        <td>XX</td>
        <td rowspan="2">TSP指数</td>
    </tr>
    <tr>
        <td>XX</td>
    </tr>
</table>

### 数据段 （无人机KeepAlive）
<table>
    <tr>
        <th>字节</th>
        <th>默认值</th>
        <th>描述</th>
    </tr>
    <tr>
        <td>1</td>
        <td>XX</td>
        <td>无人机编号</td>
    </tr>
</table>

### 帧尾 （2 Byte）  

<table>
    <tr>
        <th>字节</th>
        <th>默认值</th>
        <th>描述</th>
    </tr>
    <tr>
        <td>Byte16</td>
        <td>0xFF</td>
        <td rowspan="2">帧尾</td>
    </tr>
    <tr>
        <td>Byte17</td>
        <td>0xFF</td>
    </tr>
</table>