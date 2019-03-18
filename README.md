# iotfun

Instructions for setting up Wemos (ESP8266) used MacOS Mojave 10.14.3

# Install Arduino IDE (latest)
https://www.arduino.cc/en/Main/Software

# Install Driver for MacOS
https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers

*Restart*

On Windows/Linux might work out of the box

# Open Arduino IDE

Arduino > Preferences > Additional Boards Manager URLs:
paste
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

Tools > Board: xxxx > Boards Manager
Filter your search... type ESP8266
Select esp8266 by ESP8266 Community > Install

# Plug in Wemos

Port > /dev/cu.SLAB_USB...

File > Examples > ESP8266 > Blink

Sketch > Upload

And wemos should start blinking
