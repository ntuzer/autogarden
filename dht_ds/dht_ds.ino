#include<dht.h>
#include <OneWire.h>
#include <DallasTemperature.h>

dht DHT;
#define DHT_PIN 3
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float Celcius=0;
float Fahrenheit=0;

void setup() {
  Serial.begin(9600);
  sensors.begin();
  Serial.println("DHT11");
}


void loop() { // READ DATA
  sensors.requestTemperatures(); //DS18B20
  int chk = DHT.read11(DHT_PIN); //DHT11

  // if (digitalRead(0)>35){
  //   digitalWrite(A3, HIGH);
  //   delay(75000);
  //   digitalWrite(A3, LOW);
  // }

  Serial.println(" Humidity " );
  Serial.println(DHT.humidity, 1);
  Serial.println(" ");
  Serial.println(" Temparature ");
  Serial.println(DHT.temperature * 1.8 + 32, 1);
  Serial.println("--------------------");

  Celcius=sensors.getTempCByIndex(0);
  Fahrenheit=sensors.toFahrenheit(Celcius);


  Serial.print(" C  ");
  Serial.print(Celcius);
  Serial.print(" F  ");
  Serial.println(Fahrenheit);
  Serial.println("--------------------");
  Serial.println(" ");
  delay(2000);
}

//my
