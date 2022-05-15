package com.forest.backend.service;

import com.forest.backend.Data.SensorData;
import com.forest.backend.mapper.SensorDataMapper;
import org.springframework.scheduling.annotation.Async;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.TimeZone;

@Service
public class AsyncTaskService {

    @Resource
    SensorDataMapper sensorDataMapper;

    private final int SENSOR_DATA_PORT = 20001;  // 传感器数据接收端口

    private int byte2int(byte n) {
        if (n >= 0) return n;
        return ~n ^ 0xff;
    }
    @Async
    // 接收传感器数据
    public void sensorDataTask() {
        System.out.println("获取传感器数据任务开启");
        ServerSocket socket = null;
        try {
            socket = new ServerSocket(SENSOR_DATA_PORT);
        }
        catch (IOException e) {
            e.printStackTrace();
            return;
        }
        Socket server = null;
        InputStream is = null;
        while(true) {
            try {
                server = socket.accept();
                is = server.getInputStream();
                byte[] b = new byte[32];
                is.read(b);
                int co, co2, tsp;
                double temperature, humanity;
                temperature = b[0] + b[1] / 100.0;
                humanity = b[2] + b[3] / 100.0;
                co = (byte2int(b[4]) << 8) | byte2int(b[5]);
                co2 = (byte2int(b[6]) << 8) | byte2int(b[7]);
                tsp = (byte2int(b[8]) << 8) | byte2int(b[9]);
                System.out.printf("温度: %f, 湿度: %f, CO: %d, CO2: %d, TSP: %d\n", temperature, humanity, co, co2, tsp);
                SensorData sensorData = new SensorData(LocalDateTime.now(), temperature, humanity, co, co2, tsp);
                sensorDataMapper.insert(sensorData);
            }
            catch (IOException e) {
                e.printStackTrace();
                if (is != null) {
                    try {
                        is.close();
                    } catch (IOException e1) {
                        e1.printStackTrace();
                    }
                }
                if (server != null) {
                    try {
                        server.close();
                    } catch (IOException e1) {
                        e1.printStackTrace();
                    }
                }
                System.out.println("传感器接收任务终止");
                return;
            }
        }
    }

    @Async
    // 获取传感器状态
    public void sensorStatusTask() {
        System.out.println("获取传感器状态任务开启");
    }

    @Async
    // 获取无人机状态
    public void droneStatusTask() {
        System.out.println("获取无人机状态任务开启");
    }
}
