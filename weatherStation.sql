CREATE DATABASE wsTemp;
USE wsTemp;

CREATE TABLE WeatherStation (
    DTStamp datetime,
    DHTCelcius varchar(10),
    DHTFarenheight varchar(10),
    DHTHeatIndex varchar(10),
    DHTHumidity varchar(10),
    BaroCelcius varchar(10),
    BaroPressure varchar(10),
    WindSpeedAvg varchar(10),
    WindSpeedMin varchar(10),
    WindSpeedMax varchar(10),
    WindDirection varchar(10)
);



CREATE TABLE wsT(
	 id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
	 temp varchar(10),
 	 humidity varchar(10),
	 windSpeed varchar(10),
	 windDirection varchar(10)
	)ENGINE = MYISAM CHARACTER SET utf8 COLLATE utf8_general_ci;



CREATE TABLE wsT2(
     id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
     DateRecorded TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
     temp varchar(10),
     humidity varchar(10),
     windSpeed varchar(10),
     windDirection varchar(10)
    )ENGINE = MYISAM CHARACTER SET utf8 COLLATE utf8_general_ci;



CREATE TABLE wsT3(
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    DateRecorded TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    DHTCelcius varchar(10),
    DHTFarenheight varchar(10),
    DHTHeatIndex varchar(10),
    DHTHumidity varchar(10),
    BaroCelcius varchar(10),
    BaroPressure varchar(10),
    WindSpeedAvg varchar(10),
    WindSpeedMin varchar(10),
    WindSpeedMax varchar(10),
    WindDirection varchar(10)
    )ENGINE = MYISAM CHARACTER SET utf8 COLLATE utf8_general_ci;