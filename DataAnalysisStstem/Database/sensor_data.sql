create table if not exists sensor_data
(
    time        datetime      not null
        primary key,
    temperature decimal(5, 2) null,
    humanity    decimal(5, 2) null,
    co          int           null,
    co2         int           null,
    tsp         int           null,
    constraint sensor_data_time_uindex
        unique (time)
);

