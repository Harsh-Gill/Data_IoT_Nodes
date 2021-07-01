#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = "auth_token";
BlynkTimer timer;




const char*  Host = "google_cloud_link;
String deliverycell = "cells_to_deliver";




String uptempcell = "target_cell";
String lowtempcell = "target_cell";
String uphumicell = "target_cell";
String lowhumicell = "target_cell";
String unikeycell = "target_cell";
String truckcell = "target_cell";



int status = WL_IDLE_STATUS;

int more_text = 1; // set to 1 for more debug output

int ledPin = 23;


int delivery = 0;
int box = 0;
int sensorPin = 34;   // select the analog input pin for the photoresistor



const char* unikey = " ";
const char* destination = " ";
const char* truck = " ";








#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
const char* ssid     = "wifi_name";
const char* password = "wifi_pass";
const char* resource = "IFTT_resource";
const char* server = "maker.ifttt.com";

const char* res_email = "target_email";



uint64_t uS_TO_S_FACTOR = 10000;
uint64_t TIME_TO_SLEEP = 100;
String jsonString = "{\n";
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




#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
 
  Blynk.virtualWrite(V5, bme.readTemperature());
  Blynk.virtualWrite(V6, analogRead(sensorPin));
  Blynk.virtualWrite(V7, bme.readHumidity());
  Blynk.virtualWrite(V9, status);
 
  if (analogRead(sensorPin) <= 2000){
      box = 1;
      Serial.println("Open");
      Blynk.virtualWrite(V9, 1);
      //digitalWrite(23, HIGH);// turn the LED ON
    }
    else{
      box = 0;
      Blynk.virtualWrite(V9, 0);
      //digitalWrite(23, LOW);// turn the LED OFF
      }

}





void setup() {
    Serial.begin(115200);
    pinMode(23, OUTPUT);
    Blynk.begin(auth, ssid, password);
    initWifi();
    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));

    unsigned status;
   
    // default settings
    status = bme.begin();  
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
   
    Serial.println("-- Default Test --");
    delayTime = 1000;

    Serial.println();
    timer.setInterval(1000L, myTimerEvent);
}

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







void loop() {
  WiFiClientSecure client1;
  WiFiClient client;
 
   Blynk.run();
   timer.run(); // Initiates BlynkTimer

   Serial.println("Box status");
   Serial.println(box);
    printValues();
    delay(1000);
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
 
  const char* uptemp ="";
  const char* lowtemp ="";
  const char* uphumi ="";
  const char* lowhumi ="";
  const char* delivery ="";
 
  //--------------------------------------------------------------------uptemp
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("https://spreadsheets.google.com/feeds/cells/1MwgtgM8B8aUIvUs_m3w8P-5xoefwYhxyiUGAom98Pco/od6/public/basic/R2C3?alt=json");
    int httpCode = http.GET();
    //Check the returning code                                                                  
    if (httpCode > 0) {
      // Get the request response payload
      String payload = http.getString();
      JsonObject& root = jsonBuffer.parseObject(payload);
      // TODO: Parsing
     
      uptemp = (root["entry"]["content"]["$t"]);
      Serial.println(uptemp);
     
    }
    http.end();   //Close connection
  }
   //--------------------------------------------------------------------lowtemp
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("https://spreadsheets.google.com/feeds/cells/1MwgtgM8B8aUIvUs_m3w8P-5xoefwYhxyiUGAom98Pco/od6/public/basic/R2C2?alt=json");
    int httpCode = http.GET();
    //Check the returning code                                                                  
    if (httpCode > 0) {
      // Get the request response payload
      String payload = http.getString();
      JsonObject& root = jsonBuffer.parseObject(payload);
      // TODO: Parsing
     
      lowtemp = (root["entry"]["content"]["$t"]);
      Serial.println(lowtemp);
     
    }
    http.end();   //Close connection
  }
    //--------------------------------------------------------------------uphumi
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("https://spreadsheets.google.com/feeds/cells/1MwgtgxxxxxxxxvUs_m3w8P-5xoefwYhxyiUGAom98Pco/od6/public/basic/R2C5?alt=json");
    int httpCode = http.GET();
    //Check the returning code                                                                  
    if (httpCode > 0) {
      // Get the request response payload
      String payload = http.getString();
      JsonObject& root = jsonBuffer.parseObject(payload);
      // TODO: Parsing
     
      uphumi = (root["entry"]["content"]["$t"]);
      Serial.println(uphumi);
     
    }
    http.end();   //Close connection
  }
     //--------------------------------------------------------------------lowhumi
    if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("target_reques_cell");
    int httpCode = http.GET();
    //Check the returning code                                                                  
    if (httpCode > 0) {
      // Get the request response payload
      String payload = http.getString();
      JsonObject& root = jsonBuffer.parseObject(payload);
      // TODO: Parsing
     
      lowhumi = (root["entry"]["content"]["$t"]);
      Serial.println(lowhumi);
     
    }
    http.end();   //Close connection
  }
      //--------------------------------------------------------------------delivery status
    if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("target_request_cell");
    int httpCode = http.GET();
    //Check the returning code                                                                  
    if (httpCode > 0) {
      // Get the request response payload
      String payload = http.getString();
      JsonObject& root = jsonBuffer.parseObject(payload);
      // TODO: Parsing
     
      delivery = (root["entry"]["content"]["$t"]);
      Serial.println(delivery);
      
     
    }
    http.end();   //Close connection
  }
       
  //_______________________________________________________________________________
  //_______________________________________________________________________________
 
 
 



  Serial.println("uptemp:"+ String(uptemp));
  Serial.println("lowtemp:"+String(lowtemp));
  Serial.println("uphumi:"+String(uphumi));
  Serial.println("lowhumi:"+String(lowhumi));
  Serial.println("delivery status:"+String(delivery));

 


 
 

    if (double(bme.readTemperature()) >= 25){
      Blynk.email("kerryieda2100e@gmail.com", "Alert", "High Temperature Warning!");
      Blynk.notify("High Temperature Warning!");
    }

    else if (bme.readTemperature() <= 18) {
      Blynk.email("kerryieda2100e@gmail.com", "Alert", "Low Temperature Warning!");
      Blynk.notify("Low Temperature Warning!");

    }

    

    if (double(bme.readHumidity()) >= 65){
      Blynk.email("kerryieda2100e@gmail.com", "Alert", "High Humidity Warning!");
      Blynk.notify("High Humidity Warning!");
    }

    else if (double(bme.readHumidity()) <= 45){
      Blynk.email("kerryieda2100e@gmail.com", "Alert", "Low Humidity Warning!");
      Blynk.notify("Low Humidity Warning!");
    }
 
    if (box == 1 ){
      if ( String(delivery) == "0") {
      digitalWrite(23, HIGH);
      Blynk.email("kerryieda2100e@gmail.com", "Alert", "Changed location!");
      Blynk.notify("Wrong Delivery!");  
      }
      else {
        digitalWrite(23, LOW);
        
      }
    }

    else{
      digitalWrite(23, LOW);
    }
 




 
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

  // Temperature in Celsius (bme.readPressure()/100.0F)
 String jsonObject = String("{\"value1\":\"") + (bme.readTemperature()) + "\",\"value2\":\""
                      + bme.readHumidity() + "\",\"value3\":\"" + (bme.readPressure()/100.0F) + "\"}";
                     
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


void printValues() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure());
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");


    Serial.print("PhotoResistance = ");
    Serial.println(analogRead(sensorPin));

    Serial.println();



}
