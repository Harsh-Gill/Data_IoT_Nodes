
#include <Wire.h>
#include <LSM6.h>

LSM6 imu;

char report[80];

float ax ;
float ay ;
float az ;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();
}

void loop()
{
  imu.read();
  ax = imu.a.x ;
  ay = imu.a.y ;
  az = imu.a.z ;

  ax = ax*0.061*0.001 ;
  ay = ay*0.061*0.001 ;
  az = az*0.061*0.001 - 1.03 ;

  snprintf(report, sizeof(report), "A: %6d %6d %6d "   ,
    ax , ay , az );
  
  Serial.print("Acc. X = ");
  Serial.print(ax);
  Serial.println(" g");

  Serial.print("Acc. Y = ");
  Serial.print(ay);
  Serial.println(" g");

  Serial.print("Acc. Z = ");
  Serial.print(az);
  Serial.println(" g");


  Serial.println();

  

  delay(1000);
}
