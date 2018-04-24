#include<dht.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//DHT Initial
  dht DHT;
  #define DHT11_PIN 3

//DS18B20 Initial
  #define ONE_WIRE_BUS 5
  OneWire oneWire(ONE_WIRE_BUS);
  DallasTemperature probe(&oneWire);
  float Celcius=0;
  float Fahrenheit=0;

//Soil Initial
  const int AirValue = 518;
  const int WaterValue = 287;
  int intervals = (AirValue - WaterValue)/3;
  int soilMoistureValue = 0;

float mySensors[4] = {0,0,0,0};
int led = 13;

void setup() {
  Serial.begin(9600);
  probe.begin();
  pinMode(led, OUTPUT);
}

void loop(){
  readSensors();
  readSerialInput();

  Serial.println(toJson());
  delay(2000);
}

void readSerialInput(){
  int num = Serial.read();
  if(num == 121){
    digitalWrite(led, HIGH);
  }else if (num == 110) {
    digitalWrite(led, LOW);
  }
}

void readSensors(){
  mySensors[0] = ds18b20();
  mySensors[1] = humidity();
  mySensors[2] = temperature();
  mySensors[3] = soil();
}

String toJson(){
  String json = "{\"ds18b20\": \"" + String(mySensors[0]) +
    "\", \"humidity\": \"" + String(mySensors[1]) +
    "\", \"temperature\": \"" + String(mySensors[2]) +
    "\", \"soil\": \"" + String(mySensors[3]) + "\"}";
  return json;
}

float temperature(){
  int chk = DHT.read11(DHT11_PIN);

  // Serial.println(" Temparature ");
  // Serial.println(DHT.temperature * 1.8 + 32, 1);
  // Serial.println("--------------------");
  // Serial.println(" ");

  return DHT.temperature * 1.8 + 32;
}

float humidity(){
  int chk = DHT.read11(DHT11_PIN);

  // Serial.println(" Humidity " );
  // Serial.println(DHT.humidity, 1);
  // Serial.println(" ");
  return DHT.humidity;
}

float ds18b20(){
  probe.requestTemperatures();
  Celcius=probe.getTempCByIndex(0);
  Fahrenheit=probe.toFahrenheit(Celcius);
  // Serial.print(" C  ");
  // Serial.print(Celcius);
  // Serial.print(" F  ");
  // Serial.println(Fahrenheit);

  return Fahrenheit;
}

float soil(){
  soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
  // // Serial.println("---------------------------------");
  // // Serial.println(soilMoistureValue);
  // if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals)){
  //   Serial.println("Very Wet");
  // } else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals)) {
  //   Serial.println("Wet");
  // } else if(soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals)) {
  //   Serial.println("Dry");
  // }

  return soilMoistureValue;
}
