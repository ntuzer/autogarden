#include<dht.h>

dht DHT;
#define DHT11_PIN 3

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11");
}


void loop() { // READ DATA
  int chk = DHT.read11(DHT11_PIN);
  if (digitalRead(0)>35){
    digitalWrite(A3, HIGH);
    delay(75000);
    digitalWrite(A3, LOW);
  }
  Serial.println(" Humidity " );
  Serial.println(DHT.humidity, 1);
  Serial.println(" ");
  Serial.println(" Temparature ");
  Serial.println(DHT.temperature * 1.8 + 32, 1);
  Serial.println("--------------------");
  Serial.println(" ");
  delay(2000);
}
