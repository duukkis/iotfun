```
cd Documents/Arduino/libraries/
git clone https://github.com/adafruit/Adafruit_Sensor.git
git clone https://github.com/adafruit/DHT-sensor-library.git
```

NOTICE THE PIN NUMBERING:

If temperature sensor is connected to D4 the pin number on Arduino IDE is 2!
```
WeMos D1 mini Pin Number  	Arduino IDE Pin Number
D0 	                                16
D1 	                                5
D2 	                                4
D3 	                                0
D4 	                                2
D5 	                                14
D6 	                                12
D7 	                                13
D8 	                                15
TX 	                                1
RX 	                                3
```

The Serial.print prints into serial which in Arduino IDE can be found Tools > Serial Monitor

After upload the Serial should look something like:
```
DHTxx test!
Humidity: 25.00 %	Temperature: 24.40 *C 75.92 *F	Heat index: 23.55 *C 74.39 *F
Humidity: 24.00 %	Temperature: 24.30 *C 75.74 *F	Heat index: 23.41 *C 74.14 *F
Humidity: 25.00 %	Temperature: 24.30 *C 75.74 *F	Heat index: 23.44 *C 74.19 *F
Humidity: 25.00 %	Temperature: 24.30 *C 75.74 *F	Heat index: 23.44 *C 74.19 *F
Humidity: 25.00 %	Temperature: 24.30 *C 75.74 *F	Heat index: 23.44 *C 74.19 *F
...
```
