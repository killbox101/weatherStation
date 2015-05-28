
#include "DHT.h"
#include <Wire.h>
#include <BaroSensor.h>
#include <SPI.h>
#include <Ethernet.h>

#define DHTPIN 2  
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

const int hallPin = 12;
int hallState = 0; 

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(192,168,2,10);  // numeric IP for Google (no DNS)
IPAddress ip(192,168,2,110);
EthernetClient client;


void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600); 
    Serial.println("Starting...!");
    dht.begin();
    BaroSensor.begin();
    pinMode(hallPin, INPUT);

     if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
    }
    // give the Ethernet shield a second to initialize:
    delay(1000);
    Serial.println("connecting ehternet shield...");
   
  
}

void loop() {

  int tenMinArrayMin[2], tenMinArrayMax[2], tenMinArrayAvg[2]; //changing to 2 for testing purposes
  int oneMinArray[59];
  int oneSecArray[3];
  int qSecondCount = 0, maxVal = 0, secondTotal = 0, minVal = 25;
  int tenMinAvg, tenMinMax, tenMinMin;



  //getTemp
 
  char bufH[10], bufC[10], bufT[10], bufF[10], bufHI[10];  

  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");
  


  dtostrf(h,4,2,bufH);
  dtostrf(t,4,2,bufC);
  dtostrf(f,4,2,bufF);
  dtostrf(hi,4,2,bufHI);
  
  Serial.println(bufH);
  Serial.println(bufC);
  Serial.println(bufF);
  Serial.println(bufHI);
        
 
  
  //getBaroPress
  
  char bufBT[10], bufBP[10];
  
   if(!BaroSensor.isOK()) 
  {
    Serial.print("Sensor not Found/OK. Error: "); 
    Serial.println(BaroSensor.getError());
    BaroSensor.begin(); // Try to reinitialise the sensor if we can
  }
  else 
  {
  float baroSensorTemp = BaroSensor.getTemperature();
  float baroSensorPress = BaroSensor.getPressure();
  
  dtostrf(baroSensorTemp,4,2,bufBT);
  dtostrf(baroSensorPress,4,2,bufBP);    
  }
  
  Serial.print("This is bufT:");  
  Serial.println(bufBT);
  Serial.print("This is bufBP:");  
  Serial.println(bufBP);


//char outBuf[64];
char urlStr[200];
//String urlStr = "POST /weather4/?DHTCelcius="+ bufF;// "&DHTFarenheight="+ bufF +"&DHTHeatIndex=" +bufHI+"&DHTHumidity="+bufH+"&BaroCelcius="+bufBT+"&BaroPressure="+bufBP+ "HTTP/1.1";

sprintf(urlStr,"POST /weather4/?DHTCelcius=%s&DHTFarenheight=%s&DHTHeatIndex=%s&DHTHumidity=%s&BaroCelcius=%s&BaroPressure=%s HTTP/1.1",bufC,bufF,bufHI,bufH,bufBT,bufBP);

//sprintf(outBuf,"POST %s HTTP/1.1",urlStr);

//send to api

  if (client.connect(server, 5000)) {
    Serial.println("connected");
    // Make a HTTP request:
    //client.println("POST /weather4/?t=abc&h=def&ws=hij&wd=klm23344 HTTP/1.1");
    client.println(urlStr);
    client.println("Host: 192.168.2.10");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length:0");
    client.println("Connection: close");
    client.println();
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }

  if (client.connected())
    {
     client.stop();
    }

  //delay 20 mins
//  delay(1200000);
//10 mins
  delay(600000);
  //testing pace
//  delay(5000);

}
