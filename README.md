
This project is initiated for creating IoT based nodes for easily tracking assets or the weather at a low hardware cost and at a high data volume
# IoT Weather station Nodes / Asset tracking

_Specific sensitive information has been removed from the code. For more information, please feel free to inquire._

### 👁 Overview

The goal of this project was to create IoT based nodes for tracking assets, or the weather. Two of the primary goals for this project was to have a low hardware cost, and to provide capability of transferring large volumes of data whilst inducing minimal to non-existent cloud storage fees.

This system is capable of providing a convenient means to carrying out data analytics as data can be stored and exported at will as a csv file.

Additionally, this system can provide real-time geolocation data of each node through the use of Google's location APIs that can be called at specified intervals. It is this functionality that converts these nodes from weather trackers to asset trackers.

---
### ☁ Cloud

The data collected is stored into Google cloud. The data is sent via an API request to IFTTT which then stores the data into sheets. 

The visualization and real time-notifications can be triggered by having the MCU write to Blynk via virtual-pins.

---
### 🛠 Hardware & Tools Used


There are 2 hardware components: 
* Set A: 
    * Acts as an incoming processing server, collecting data relating to its environment like temperature, humidity, light intensity and air pressure
* Set B:
    * Acts as a server node, which can detect the Geolocation API of the current location, give acceleration data of the target if it is moving and can be configured to receive incoming data from Set A

For potential scaling of system in the future, Azure IoTHub connection code has also been tested and executed. The usage of Azure IoHub allows for much larger volumes of data and greater analysis capabilities. The code for that can be found here in this repository.

#### Hardware Used

| Item       | Usage                                  |
|------------|----------------------------------------|
| ESP32      | Microcontroller Unit (MCU)             |
| LSM6DS33   | 3D Accelerometer and Gyrometer         |
| BME280     | Temperature, Humidity, Pressure Sensor |
| Simple LED | Notification Light                     |

#### Software Used

| Software     | Usage                                 |
|--------------|---------------------------------------|
| Google Cloud | Data Storage                          |
| Blynk        | Data Platform for Visualizing         |
| IFTTT        | Channel Builder for APIs and Webhooks |

---

### 📷 Images

_**Set A Exterior**_
<img width="895" alt="螢幕截圖 2021-07-01 上午10 26 20" src="https://user-images.githubusercontent.com/56172862/124055634-d590a080-da56-11eb-8a4b-d74912ac6dfb.png">

_**Set A Interior**_

<img width="407" alt="螢幕截圖 2021-07-01 上午10 29 56" src="https://user-images.githubusercontent.com/56172862/124055892-52237f00-da57-11eb-9ec5-5f7347e8c18a.png">

_@Caton for Hardware Assembly_
