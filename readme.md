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

