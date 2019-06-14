create database meteo;
use meteo;
grant all on meteo.* to 'meteo'@'localhost' identified by 'meteopass';
create table pressure (id bigint unsigned primary key auto_increment not null, sensorID int unsigned not null, time datetime not null, pa float not null, mmhg float not null);
create table temperature (id bigint unsigned primary key auto_increment not null, sensorID int unsigned not null, time datetime not null, temperature float not null);
create table humidity (id bigint unsigned primary key auto_increment not null, sensorID int unsigned not null, time datetime not null, humidity float not null);
