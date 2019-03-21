# iot fun

Instructions for setting up Wemos (ESP8266) used MacOS Mojave 10.14.3

# Install Arduino IDE (latest)
https://www.arduino.cc/en/Main/Software

# Install Driver for MacOS
https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers

*Restart*

On Windows/Linux things work out of the box

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

# Examples

- Oled - how to set the Oled screen
- Temperature - how to set the temperature meter
- Moisture - how to set soil moisture detector
- Wifi - how to connect to Internet and send some data
- Complete - All of the above bind together
