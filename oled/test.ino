#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
// the driver is for 128x64 screen so the display needs some tweaking
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET); 

// set up stuff 
void setup()   {
  Serial.begin(9600);
 
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  // init done
  display.display();
  delay(2000);
 
  // Clear the buffer.
  display.clearDisplay();
 
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
 // move cursor 32 pixels right (the driver is for 128 wide)
  display.setCursor(32,20);
  display.println("Hello, world!");
  display.display();
  delay(2000);
  display.clearDisplay();
 
}
 
int i = 0;
void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(32,10);
  display.print("T= ");
  display.println(i);
  display.display();
  i++;
  delay(1000);  
}
