package com.forest.backend.Data;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class SensorData {
    private String num;
    private Double temperature;
    private Double humanity;
    private Integer co2;
    private Integer co;
    private Integer tsp;
}
