
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


void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600); 
    Serial.println("Starting...!");
    dht.begin();
    BaroSensor.begin();
    pinMode(hallPin, INPUT);
   
  
}

void loop() {

  int tenMinArrayMin[2], tenMinArrayMax[2], tenMinArrayAvg[2]; //changing to 2 for testing purposes
  int oneMinArray[59];
  int oneSecArray[3];
  int qSecondCount = 0, maxVal = 0, secondTotal = 0, minVal = 25;
  int tenMinAvg, tenMinMax, tenMinMin;

  
  //get wind speed

  char bufWSAvg[10], bufWSMin[10], bufWSMax[10];
  
  //ten min interval
  for (int i=0; i<1; i++)
  {

    int avgTotal = 0, minTotal = 0, maxTotal = 0;

     //minutes interval 
     for (int i=0; i<59 ; i++) 
     {

       int secondsTotal = 0;
       int oneSecAverage = 0;
       
        //quater seconds interval 
        for (int x=0; x<4; x++)
        {
          int Count = 0;
          unsigned long currentT = millis();

          while(millis() < currentT + 250)
          {
            hallState = digitalRead(hallPin);
          //second interval pulling quater second rotations
            if (hallState == LOW)
            {
             Count ++ ;
             delay(10);
             //Serial.println("Hit Hi");
            }
            
          }
          
         secondsTotal += Count;
         //Serial.print("This is our Count: ");
         Serial.println(Count);
         //Serial.println();
         //Serial.print("This is our Seconds Total: ");
         //Serial.print(secondsTotal);
         //Serial.println();
        }
        Serial.print("Saving our average: ");
        oneSecAverage = secondsTotal/4;
        
        oneMinArray[i] = oneSecAverage;
        Serial.println(oneSecAverage);
        //get min max and avg pass to 10 minute arrays
     }

     //get avg over the minute
     for (int i=0; i < 59; i++)
     {
       avgTotal += oneMinArray[i];
     }
     avgTotal = avgTotal/60;
     tenMinArrayAvg[i] = avgTotal;
     
     //get max over the minute
     
     for (int i=0; i < 59; i++)
     {
       if (oneMinArray[i] > maxVal)
       {
         maxVal = oneMinArray[i];
       }
     }
     tenMinArrayMax[i] = maxVal;
     
     //get min over the minute
     for (int i=0; i < 59; i++)
     {
       if (oneMinArray[i] > minVal)
       {
         minVal = oneMinArray[i];
       }
     }
     tenMinArrayMin[i] = minVal;

     Serial.println("Values over one min: ");
     for (int i = 0; i <59; i++)
     {

      Serial.print(oneMinArray[i]);
      Serial.print(",") ;
     }

     Serial.println();
     Serial.print("Max over minute:");
     Serial.print(maxVal);
     Serial.println();

     Serial.print("Min over minute:");
     Serial.print(minVal);
     Serial.println();


     Serial.print("Avg over minute:");
     Serial.print(avgTotal);
     Serial.println();

     
  }
 
  //get avg over the minute
   for (int i=0; i < 1; i++) //changing to 2 for testing purposes
   {
     tenMinAvg += tenMinArrayAvg[i];
   }
   tenMinAvg = tenMinAvg/2;  //changing to 2 for testing purposes
   tenMinAvg = tenMinAvg;
   
   //get max over the minute
   
   for (int i=0; i < 1; i++) //changing to 2 for testing purposes
   {
     if (tenMinArrayMax[i] > maxVal)
     {
       maxVal = tenMinArrayMax[i];
     }
   }
   tenMinMax = maxVal;
   
   //get min over the minute
   for (int i=0; i < 1; i++) //changing to 2 for testing purposes
   {
     if (tenMinArrayMin[i] > minVal)
     {
       minVal = tenMinArrayMin[i];
     }
   }
   tenMinMin = minVal;

   Serial.println("Ten Min minimum Array: ");

   for (int i = 0; i<1, i++;)
   {
    Serial.print(tenMinArrayMin[i]);
    Serial.print(",");
   }
   Serial.println();

  Serial.println("Ten Min maximum Array: ");

  for (int i = 0; i<1, i++;)
   {
    Serial.print(tenMinArrayMax[i]);
    Serial.print(",");
   }
   Serial.println();

   Serial.println("Ten Min average Array: ");


  for (int i = 0; i<1, i++;)
   {
    Serial.print(tenMinArrayAvg[i]);
    Serial.print(",");
   }
   Serial.println();
   
   Serial.print(" Ten Min Min:");
   Serial.print(tenMinMin);
   Serial.println();
   Serial.print("Ten Min Max:");
   Serial.print(tenMinMax);
   Serial.println();
   Serial.print("Ten Min Avg:");
   Serial.print(tenMinAvg);
   Serial.println();
   
   dtostrf(tenMinMin,4,2,bufWSMin);
   dtostrf(tenMinMax,4,2,bufWSMax);
   dtostrf(tenMinAvg,4,2,bufWSAvg);


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
  
  
  Serial.println(bufBT);
  Serial.println(bufBP);


//send to api

  



  delay(1000);

}