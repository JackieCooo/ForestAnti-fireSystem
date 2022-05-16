## **数据包格式**  
<table>
    <tr>
        <th>字节</th>
        <th>默认值</th>
        <th>描述</th>
    </tr>
    <tr>
        <td>Byte1</td>
        <td>0xAA</td>
        <td rowspan="3">前导字符</td>
    </tr>
    <tr>
        <td>Byte2</td>
        <td>0xAA</td>
    </tr>
    <tr>
        <td>Byte3</td>
        <td>0xAA</td>
    </tr>
    <tr>
        <td>Byte4</td>
        <td>XX</td>
        <td>
            数据包类型<br />
            0x01: 传感器数据<br />
            0x02: 传感器KeepAlive<br />
            0x03: 无人机KeepAlive<br />
        </td>
    </tr>
    <tr>
        <td>Byte5</td>
        <td>XX</td>
        <td>数据包总长</td>
    </tr>
    <tr>
        <td>Byte6</td>
        <td>XX</td>
        <td>温度整数</td>
    </tr>
    <tr>
        <td>Byte7</td>
        <td>XX</td>
        <td>温度小数</td>
    </tr>
    <tr>
        <td>Byte8</td>
        <td>XX</td>
        <td>湿度整数</td>
    </tr>
    <tr>
        <td>Byte9</td>
        <td>XX</td>
        <td>湿度小数</td>
    </tr>

</table>