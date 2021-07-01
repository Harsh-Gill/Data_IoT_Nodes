#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


#include <Wire.h>
#include <LSM6.h>

LSM6 imu;

char report[80];

float ax ;
float ay ;
float az ;
char auth[] = "auth_token";



#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
// Replace with your SSID and Password
const char* ssid     = "wifi_name";
const char* password = "wifi_pass";

// Replace with your unique IFTTT URL resource
const char* resource = "IFTTT_resource";

// How your resource variable should look like, but with your own API KEY (that API KEY below is just an example):
//const char* resource = "/trigger/bme280_readings/with/key/nAZjOphL3d-ZO4N3k64-1A7gTlNSrxMJdmqy3";

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

// Time to sleep
uint64_t uS_TO_S_FACTOR = 10000;  // Conversion factor for micro seconds to seconds
// sleep for 30 minutes = 1800 seconds
uint64_t TIME_TO_SLEEP = 100;

const char* Host = "www.googleapis.com";
String thisPage = "geo_key";
String key = "geo_string";

int status = WL_IDLE_STATUS;
String jsonString = "{\n";

double latitude    = 0.0;
double longitude   = 0.0;
double accuracy    = 0.0;
int more_text = 1; // set to 1 for more debug output


BlynkTimer timer;
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V10, az);
  Blynk.virtualWrite(V11, ax);
  Blynk.virtualWrite(V12, ay);
  Blynk.virtualWrite(V13, 1, latitude, longitude, "value");
}



static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
 
};







// Uncomment to use BME280 SPI
/*#include <SPI.h>
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10*/

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

void setup() {
 
  Serial.begin(9600);
  Wire.begin();

  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();
    Blynk.begin(auth, ssid, password);

 
 

  initWifi();
  //makeIFTTTRequest();
  timer.setInterval(1000L, myTimerEvent);
   
}





// Establish a Wi-Fi connection with your router
void initWifi() {
  Serial.print("Connecting to: ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);  

  int timeout = 10 * 4; // 10 seconds
  while(WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if(WiFi.status() != WL_CONNECTED) {
     Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: ");
  Serial.print(millis());
  Serial.print(", IP address: ");
  Serial.println(WiFi.localIP());
}







// Make an HTTP request to the IFTTT web service
//void makeIFTTTRequest() {
 void loop(){
  imu.read();
  ax = imu.a.x ;
  ay = imu.a.y ;
  az = imu.a.z ;

  ax = ax*0.061*0.001 ;
  ay = ay*0.061*0.001 ;
  az = az*0.061*0.001  ;

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
  Blynk.run();
  timer.run(); // Initiates BlynkTimer







 
  char bssid[6];
  DynamicJsonBuffer jsonBuffer;
  Serial.println("scan start");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found...");

    if (more_text) {
      // Print out the formatted json...
      Serial.println("{");
      Serial.println("\"homeMobileCountryCode\": 234,");  
      Serial.println("\"homeMobileNetworkCode\": 27,");   
      Serial.println("\"radioType\": \"gsm\",");          
      Serial.println("\"carrier\": \"Vodafone\",");      
      //Serial.println("\"cellTowers\": [");                
      //Serial.println("],");
      Serial.println("\"wifiAccessPoints\": [");
      for (int i = 0; i < n; ++i)
      {
        Serial.println("{");
        Serial.print("\"macAddress\" : \"");
        Serial.print(WiFi.BSSIDstr(i));
        Serial.println("\",");
        Serial.print("\"signalStrength\": ");
        Serial.println(WiFi.RSSI(i));
        if (i < n - 1)
        {
          Serial.println("},");
        }
        else
        {
          Serial.println("}");
        }
      }
      Serial.println("]");
      Serial.println("}");
    }
    Serial.println(" ");
  }
  // now build the jsonString...
  jsonString = "{\n";
  jsonString += "\"homeMobileCountryCode\": 234,\n"; 
  jsonString += "\"homeMobileNetworkCode\": 27,\n";  
  jsonString += "\"radioType\": \"gsm\",\n";        
  jsonString += "\"carrier\": \"Vodafone\",\n";   
  jsonString += "\"wifiAccessPoints\": [\n";
  for (int j = 0; j < n; ++j)
  {
    jsonString += "{\n";
    jsonString += "\"macAddress\" : \"";
    jsonString += (WiFi.BSSIDstr(j));
    jsonString += "\",\n";
    jsonString += "\"signalStrength\": ";
    jsonString += WiFi.RSSI(j);
    jsonString += "\n";
    if (j < n - 1)
    {
      jsonString += "},\n";
    }
    else
    {
      jsonString += "}\n";
    }
  }
  jsonString += ("]\n");
  jsonString += ("}\n");
  //--------------------------------------------------------------------

  Serial.println("");
  WiFiClientSecure client1;
  WiFiClient client;
 
  //Connect to the client and make the api call
  Serial.print("Requesting URL: ");
  Serial.println("https://" + (String)Host + thisPage + key);
  Serial.println(" ");
  if (client1.connect(Host, 443)) {
    Serial.println("Connected");
    client1.println("POST " + thisPage + key + " HTTP/1.1");
    client1.println("Host: " + (String)Host);
    client1.println("Connection: close");
    client1.println("Content-Type: application/json");
    client1.println("User-Agent: Arduino/1.0");
    client1.print("Content-Length: ");
    client1.println(jsonString.length());
    client1.println();
    client1.print(jsonString);
    delay(500);
  }

  //Read and parse all the lines of the reply from server
  while (client1.available()) {
    String line = client1.readStringUntil('\r');
    if (more_text) {
      Serial.print(line);
    }
    JsonObject& root = jsonBuffer.parseObject(line);
    if (root.success()) {
      latitude    = root["location"]["lat"];
      longitude   = root["location"]["lng"];
      accuracy   = root["accuracy"];
    }
  }

  Serial.println("closing connection");
  Serial.println();
  client1.stop();

  Serial.print("Latitude = ");
  Serial.println(latitude, 6);
  Serial.print("Longitude = ");
  Serial.println(longitude, 6);
  Serial.print("Accuracy = ");
  Serial.println(accuracy);

  delay(2000);
 
  Serial.print("Connecting to ");
  Serial.print(server);
 
 
  int retries = 5;
  while(!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
 
  Serial.print("Request resource: ");
  Serial.println(resource);
 
 
 
  String lat = String(latitude, 6);
  String lon = String(longitude, 6);

 
  // Temperature in Celsius
  String jsonObject = String("{\"value1\":\"") + lat +","+ lon + "\",\"value2\":\"" +ax+","+ay+","+az
                      + "\"}";

  // Comment the previous line and uncomment the next line to publish temperature readings in Fahrenheit                    
  /*String jsonObject = String("{\"value1\":\"") + (1.8 * bme.readTemperature() + 32) + "\",\"value2\":\""
                      + (bme.readPressure()/100.0F) + "\",\"value3\":\"" + bme.readHumidity() + "\"}";*/
                     
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server);
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);


  int timeout = 5 * 10; // 5 seconds            
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());
  }
 
  Serial.println("\nclosing connection");
  client.stop();
}
