create table if not exists user
(
    id       int auto_increment,
    name     varchar(20) not null,
    password varchar(50) not null,
    constraint user_id_uindex
        unique (id)
);

