package com.forest.backend;

import com.forest.backend.service.AsyncTaskService;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;

@SpringBootApplication
public class BackEndApplication {

    public static void main(String[] args) {
        ConfigurableApplicationContext context = SpringApplication.run(BackEndApplication.class, args);

        AsyncTaskService asyncTaskService = context.getBean(AsyncTaskService.class);
        asyncTaskService.sensorDataTask();
        asyncTaskService.sensorStatusTask();
        asyncTaskService.droneStatusTask();

        System.out.println("所有任务已启动");
    }

}
