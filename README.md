# FileSystem_Oper

This program is in C++ and it applies a File Allocation Table.

# Authors
Ximena Marín Sánchez C14448
Aron Hidalgo Gómez C23880
Quiann Zolfaghari Calderón C18723
Nathalie Alfaro Quesada B90221
José Pablo Mora Cubillo B75044

# How to execute
First, install `openssl`:
```
sudo apt install libssl-dev
```

To compile and execute this program the Compiler is C++, and you can use the Compiler of your preference, for example GCC.

```
g++ main.cpp FAT.cpp Usuario.cpp Authenticator.cpp HashHandler.cpp -o main -lssl -lcrypto
```

```
./main
```

## Description of sensor situation:
1. Sensor of temperature and humidity: In an intelligent building it can be useful for a computer server room. The sensor applied in the project is DHT-11.

2. Infrared: It is used to identify white and black, also during the project we capture the data with and without the remote control of the classroom in order to see how the data changed. In an intelligent building infrared sensor can be used for detecting body heat.

3. Ultrasonic: The HC-SR04 is composed of two ultrasonic transducers. One which outputs ultrasonic sound pulses and the other is receiver (listens for reflected waves)

4. Photoresistor: It is a light-controlled variable resistor, it decreases with the increasing incident. In the Intel Galileo, we used for base the next model in the tool Tinkercad.
