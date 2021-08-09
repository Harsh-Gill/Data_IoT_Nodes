# IoT Weather station Nodes / Asset tracking

(Specific sensitive info. has been removed from code, for info. please feel free to inquire)

This project is initiated for creating IoT based nodes for easily and tracking assets or the weather at a low hardware cost and at a high volume but almost free of cost cloud storage. With convenient analytics as data can be conveniently stored as csv and exported at wanted intervals. It can also provide real-time geolocation information of each node using Googles Location APIs that are called every X seconds. This is optional for converting weather nodes into asset-trackers.

The data is stored into Google cloud. The data is sent by sending an API request to IFTTT which then can store the data into sheets. 
The visualization and real time-notifications can be triggered by having the MCU write to Blynk via virtual-pins.


There are 2 hardware components; a set A and set B. set A acts as an incoming processing server and set B acts as nodes of this server to send real-time data. Set B then takes the incoming data and puts them onto the cloud and notifies of potential alarms.


For future/potential scaling of system, Azure IoTHub connection code has also been tested and executed, the code is in the repo. as well, this allows for much larger volumes of data volume and analysis.

---
For this project

The hardwares used are:

ESP32 - MCU

LSM6DS33 - 3D Accelerometer and Gyrometer

BME280 - Temp/Humid/Pressure sensor

Simple LED - Notification 

The software used are:

Google Cloud
Blynk
IFTTT



<img width="895" alt="螢幕截圖 2021-07-01 上午10 26 20" src="https://user-images.githubusercontent.com/56172862/124055634-d590a080-da56-11eb-8a4b-d74912ac6dfb.png">


<img width="407" alt="螢幕截圖 2021-07-01 上午10 29 56" src="https://user-images.githubusercontent.com/56172862/124055892-52237f00-da57-11eb-9ec5-5f7347e8c18a.png">


@Caton for Hardware Assembly
