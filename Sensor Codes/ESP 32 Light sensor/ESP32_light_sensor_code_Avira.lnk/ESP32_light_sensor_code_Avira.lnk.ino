int sensorPin = 34;   // select the analog input pin for the photoresistor

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(analogRead(sensorPin));
  delay(900);
} 
