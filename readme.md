#To Run the Webserver on x86x84

docker build -t my-apache2 .
docker run -p 8080:80 -dit --name my-running-app my-apache2

#To Run webserver on ARM

cd to web folder
docker build -t ws_web
docker run -p 8080:80 -dit --name weather_station_web ws_web


docker run -p 8080:80 -d mysite

#until commands

docker exec -i -t b01b68bef8e6 /bin/bash








#To Run the Webserver

docker build -t my-apache2 .
docker run -p 8080:80 -dit --name my-running-app my-apache2


docker run -p 8080:80 -d mysite

#until commands

docker exec -i -t b01b68bef8e6 /bin/bash
docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' f4af320dfc38d66a269cb3a67b836a18ca7033267f108c75e7bb23eaff205241

https://nodejs.org/en/docs/guides/nodejs-docker-webapp/



#db 

docker rm -f test-mysql

docker run --detach --name=test-mysql --env="MYSQL_ROOT_PASSWORD=mypassword" --publish 6603:3306 hypriot/rpi-mysql     <----- this command works for starting the container!!

docker run --detach --name=test-mysql --env="MYSQL_ROOT_PASSWORD=mypassword" "MYSQL_USER=wsUpdate" "MYSQL_PASSWORD=password" "MSQL_DATABASE=wsTemp" --publish 6603:3306 hypriot/rpi-mysql


docker run --detach --name=test-mysql --env=MYSQL_ROOT_PASSWORD=mypassword --env=MYSQL_USER=wsUpdate --env=MYSQL_PASSWORD=password --env=MSQL_DATABASE=wsTemp --publish 3306:3306 hypriot/rpi-mysql

docker run hypriot/rpi-mysql --name some-mysql  -e MYSQL_ROOT_PASSWORD=my-secret-pw  -v /my/custom:/etc/mysql/conf.d

<-------

docker exec -it test-mysql bash
mysql -u root -p  (prompt for password)

docker exec -i some-mysql mysql -u root -p mypassword < weatherStation.sql <-- optional


show databases; <-- list avail dbs

create database wsTemp;
use wsTemp;

CREATE TABLE wsT4(
    id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    DateRecorded TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    DHTCelcius float,
    DHTFarenheight float,
    DHTHeatIndex float,
    DHTHumidity float,
    BaroCelcius float,
    BaroPressure float
   )ENGINE = MYISAM CHARACTER SET utf8 COLLATE utf8_general_ci;    


--CREATE USER 'wsUpdate'@'localhost' IDENTIFIED BY 'password';

grant all privileges on wsTemp.* to wsUpdate@localhost identified by 'password';

  ------>

  
INSERT INTO wsT4 (DHTCelcius,DHTFarenheight,DHTHeatIndex,DHTHumidity,BaroCelcius,BaroPressure) values ('1','1','1','1','1','1');
INSERT INTO wsT4 (DHTCelcius,DHTFarenheight,DHTHeatIndex,DHTHumidity,BaroCelcius,BaroPressure) values ('2','2','2','2','2','2');


#removing old containers and their associated images

docker rm -f ws_api
docker rmi weather_station_api