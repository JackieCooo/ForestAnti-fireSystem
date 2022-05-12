package com.forest.backend.service;

import org.springframework.scheduling.annotation.Async;
import org.springframework.stereotype.Service;

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

@Service
public class AsyncTaskService {

    private final int SENSOR_DATA_PORT = 20001;  // 传感器数据接收端口
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
                byte[] b = new byte[1024];
                int len = is.read(b);
                System.out.println(new String(b, 0, len));
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
