ATI nano25 Force and Torque Sensor Usage
========

# Hardware Setting
### 1. Preparing Hardwares: The simplest way is shown in the following figures. You need to prepare the following items: a 12V to 24V DC power supply, two wires together with the sensor provided by ATI, the sensor, a RJ45 Ethernet cable. And then connect them as figure 2.
![](Files/figure1)
![](Files/figure2)

### 2. Setting up Network in your Computer: Set the network in Ubuntu according to figure 3. Open http://192.168.1.1 after setting. If you can connect to the link normally, the sensor can be used.
![](Files/figure3)

# The Most Convenient Method
### You can use my demo to obtain force and torque data and calibrate the sensor.
```
cd NetFT-demo
```
```
pip install NetFT
```
```
python main.py
```

# Custom Method
### You can also set your own functions. For python version, you can change the code and achieve it through the following commands. There is also C++ version in /NetFT-C++.
```
cd NetFT-python
python setup.py install.
```