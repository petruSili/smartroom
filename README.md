<!-- PROJECT LOGO -->
<div align="center">
  <a href="https://www.youtube.com/watch?v=8VIFxMETGF0"><img src="Images/Intro.jpg" alt="Logo" width="800"></a>
  <h1 align="center">Smart Room</h1>
  <p align="center">
  A fully local smart home system built with largely available hardware components. It is based on ESP and Arduino platforms.
  MQTT is used as the main communication protocol. 
  </p>
</div>
<br />
<br />
<br />

## Overview
<div align="center">
  <img src="Images/Overview.png" alt="Overview" width="600">  
</div>
<br />
<br />
<!-- TABLE OF CONTENTS -->
<details>
  <summary>Components</summary>
  <ul>
    <li><a href="#controlbox">ControlBox</a></li>
    <li><a href="#sensorbox">SensorBox</a></li>
    <li><a href="#arduinofan">ArduinoFan</a></li>
    <li><a href="#controller">Controller</a></li>
    <li><a href="#mobileapp">MobileApp</a></li>
  </ul>
</details>
<br />
<br />
<p>
  The system manages 3 points of light and the airflow in a room. It has two modes of operation: 
</p> 
<ul>
  <li>
    <p>
      Manual<br/>
      the user can interact with the devices by using the ControlBox, in fact touching the black metal plates turns the devices ON and OFF and the dial on top can be used to select a device and set its intensity(fan speed, light intensity). The same can be done through the android app.
    </p> 
  </li>
  <li>
    <p>
      Auto<br/>this mode is enabled by the user through the app. When enabled the controller manages the devices according to the scenario, sensor data and user defined settings. The following image shows the general flow control.
    </p>
    <div align="center">
      <img src="Images/AutoMode1.jpg" alt="AutoMode1.jpg" width="600">
    </div>
  </li>
</ul>

<!-- CONTROLBOX -->
## ControlBox
<img align="right" src="Images/ControlBox1.jpg" alt="ControlBox1.jpg" width="250">
This device is a control panel that lets the user to interact with some of the devices. It has 3 capacitive sensors made with metal plates that function as toggle buttons. On top it has a Rotary Encoder with an integrated switch button. By pushing the button the user can select a device and by rotating the dial a new intensity level can be set for the specified device. At the bottom there is a LED Ring that is programmed to give the user visual feedback on the performed actions. The device is always listening for messages regarding the devices it can control to keeo in sync with their states.
<br />
<br />
<br />
<br />
<br />
<br />
<details align="right">
  <summary>More</summary>
  <div align="center">
    <img src="Images/ControlBox2.jpg" alt="ControlBox2.jpg" width="600">
  </div>
  <br />
  <div align="center">
    <img src="Images/ControlBox3.jpg" alt="ControlBox3.jpg" width="600">
  </div>
  <br /> 
  <div align="center">
    <img src="Images/ControlBox4.jpg" alt="ControlBox4.jpg" width="600">
    <p align="center"><pre>
      1. Rotary Encoder KY-040          2. WS2812B 5050 RGB LED Ring
    </pre></p> 
  </div>
</details>

<!-- SENSORBOX -->
## SensorBox
<img align="right" src="Images/SensorBox1.jpg" alt="SensorBox1.jpg" width="250">
This is a simple multisensor that reads the temperature, humidity, light intensity and motion in a room. The data is mainly used by the system when operating in Auto Mode. Temperature and humidity are also shown in the app.
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<details align="right">
  <summary>More</summary>
  <div align="center">
    <img src="Images/SensorBox2.jpg" alt="SensorBox2.jpg" width="600">
  </div>
  <br />
  <div align="center">
    <img src="Images/SensorBox3.jpg" alt="SensorBox3.jpg" width="600">
  </div>
  <br />
  <div align="center">
    <img src="Images/SensorBox4.jpg" alt="SensorBox4.jpg" width="600">
    <p align="center"><pre>
      1. TSL2591       2.PIR AM312      3.Temp/Hum DHT22
    </pre></p> 
  </div>
</details>

<!-- ARDUINOFAN -->
## ArduinoFan
<img align="right" src="Images/ArduinoFan1.jpg" alt="ArduinoFan1.jpg" width="250">
The fan is built with a 3-phase BLDC motor salvaged from an old printer. An Electronic Speed Controller(ESC) powered by an external power supply is used to syncronize the three phases and thus controlling the speed. The system Controller(Arduino) communicates with the ESC through the Data pin with PWM.
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<details align="right">
  <summary>More</summary>
  <div align="center">
    <img src="Images/ArduinoFan2.jpg" alt="ArduinoFan2.jpg" width="600">
  </div>
  <br />
  <div align="center">
    <img src="Images/ArduinoFan3.jpg" alt="ArduinoFan3.jpg" width="600">
  </div>
</details>

<!-- CONTROLLER -->
## Controller
<img align="right" src="Images/Controller.jpg" alt="Controller.jpg" width="250">
The Controller is the heart of the system. Its role is better understood through its interactions with other devices:
<ul>
  <li>
    SensorBox: <br/>
    keeps track of the temperature, humidity and motion in the room.
  </li>
    <li>
    ControlBox: <br/>
    answers to update requests from the ControlBox when it first boots up. Also sends it in sleep mode when nobody is home to save power.
  </li>
  <li>
    MobileApp: <br/>
    the Controller functions as a medium between the app and the rest of the system by implementing an HTTP server. It answers to update requests and forwards the commands     coming from the app.
  </li>
  <li>
    BLE Scanner: <br/>
    keeps track of user's presence in the house. 
  </li>
</ul>
In terms of hardware the Controller runs on an Arduino Mega 2560 coupled with an Ethernet Shield (W5100 R3).
<br />
<br />
<br />

<!-- MOBILEAPP -->
## MobileApp
<img align="right" src="Images/MobileApp.jpg" alt="MobileApp.jpg" width="250">
A very simple Android App that shows Temperature, Humidity and the states of the controllable devices. It keeps updated by polling the data from the Controller. Through the app the user can also enable the Auto Mode which when enabled reveals the toggle for the Sleep Mode.
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
<br />
