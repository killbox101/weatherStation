from hypriot/rpi-mysql
ENV MYSQL_ROOT_PASSWORD=mypassword
ENV MYSQL_USER=wsUpdate
ENV MYSQL_PASSWORD=password

EXPOSE 3306

RUN mypassword| mysql -u root -p
RUN create database wsTemp;
RUN use wsTemp;

#RUN CREATE TABLE wsT4( id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
#     DateRecorded TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
#     DHTCelcius float,
#     DHTFarenheight float,
#     DHTHeatIndex float,
#     DHTHumidity float,
#     BaroCelcius float,
#     BaroPressure float
#     )ENGINE = MYISAM CHARACTER SET utf8 COLLATE utf8_general_ci;



