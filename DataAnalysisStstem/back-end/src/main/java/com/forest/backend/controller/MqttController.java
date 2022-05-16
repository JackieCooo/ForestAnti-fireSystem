package com.forest.backend.controller;

import com.forest.backend.Data.SensorData;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

@RestController
@RequestMapping("/mqtt")
public class MqttController {

    @PostMapping("/data")
    public String uploadData(@RequestBody SensorData sensorData) {
        System.out.println(sensorData);
        return "ok";
    }

    @PostMapping("/test")
    public void testPort(@RequestBody Map<String, Object> params) {
        System.out.println(params);
    }
}
