const int AirValue = 518;   //you need to replace this value with Value_1
const int WaterValue = 287;  //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;
int soilMoistureValue = 0;

// Dry: (520 430]
// Wet: (430 350]
// Water: (350 260]


void setup() {
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
}

void loop() {
  soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
  Serial.println("---------------------------------");
  Serial.println(soilMoistureValue);
  if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals)){
    Serial.println("Very Wet");
  } else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals)) {
    Serial.println("Wet");
  } else if(soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals)) {
    Serial.println("Dry");
  }

  delay(100);
}
