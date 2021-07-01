// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4.


void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
  pinMode(23, OUTPUT);
  digitalWrite(23, LOW);
  
 
}

void loop()
{
  Serial.println(touchRead(T0));  // get value using T0
      if(touchRead(T0) < 50)
    {
     digitalWrite(23, HIGH);// turn the LED ON
       
    }
    else {
      digitalWrite(23, LOW);// turn the LED ON
    }
    
  delay(1000);

}
