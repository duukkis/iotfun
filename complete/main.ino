#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const String slack_icon_url = ":red_chili:"; // not working yet
const String slack_username = "Chiliplant";

const char* host = "hooks.slack.com";
const char* fingerprint = "C1 0D 53 49 D2 3E E5 2B A2 61 D5 9E 6F 99 0D 3D FD 8B B2 B3";
const char* webhookUrl = "/services/AAAAAA/BBBBBB/cccccccddddeeee";

/*
 WIFI CONFIGURATION
 */
char SSID[] = "SSID";
char pwd[] = "SSID_PASS";

/*
 * soil moisture stuff
 */
#define PIN_MOISTURE_VOLTAGE 12     // PIN D6
#define POST_INTERVAL_SECONDS 10
// WATER GLASS 195
// DRY 609 - the dry is 447 when power is connected to D6 (so check the values)
#define MIN_WETNESS 77
#define MAX_WETNESS 471
/*
 * temperature
 */
#define DHTPIN 13     // what pin we're connected to 13 equals D7
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

/*
 * Oled screen
 */
#define OLED_RESET 0  // GPIO0

// driver is for 128 by 64 so we need some tweaking
Adafruit_SSD1306 display(OLED_RESET); 

void setup() {
  // ---------- WIFI
  Serial.begin(9600);
  WiFi.begin(SSID, pwd);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  // ---------- SOIL MOISTURE
  pinMode(PIN_MOISTURE_VOLTAGE, OUTPUT); // PIN
  // ---------- AIR TEMPERATURE
  dht.begin();
  // ---------- OLED SCREEN
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  // init done
  display.display();
}

int timer = 0;

void loop() {
  // ----------- SOIL MOISTURE
  if (timer > POST_INTERVAL_SECONDS){
    // MOISTURE

    // set the soil moisture on
    digitalWrite(PIN_MOISTURE_VOLTAGE, HIGH); // PIN set power to meter
    delay(2000); // PIN wait for the meter to start
    timer = 0;
    int val = analogRead(0);
    Serial.println(val);
    Serial.println(calculatePersentage(val));
    digitalWrite(PIN_MOISTURE_VOLTAGE, LOW); // PIN turn off power to meter

    // TEMPERATURE

    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.println();

    // SCREEN
    showTextOnDisplay("M:" + String(calculatePersentage(val)), "T: " + String(t), "H:" + String(h));
  } else {
    timer++;
  }
  delay(1000);

}

// Set cursor to x=33 and y=8 as the driver is for bigger screen
void showTextOnDisplay(String msg, String msg2, String msg3){
  display.clearDisplay();
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(33,8);
  display.print(msg);
  display.setCursor(33,16);
  display.print(msg2);
  display.setCursor(33,24);
  display.print(msg3);
  display.display();
}

// wifi reconnect, not tested
void reconnect() {  
  Serial.print("Reconnecting");
  WiFi.mode(WIFI_STA);  
  WiFi.begin(SSID, pwd);  
  while (WiFi.status() != WL_CONNECTED) {  
      delay(500);  
      Serial.print(".");
  }  
  Serial.println("Connected!");
}  

int calculatePersentage(int moisture){
  if (moisture > MAX_WETNESS) {
    return 0;
  } else if (moisture < MIN_WETNESS) {
    return 100;
  } else { // calculate actual persentage
    moisture = moisture - MIN_WETNESS;
    // subtract from 100 cause the scale is upside down
    return 100 - (((moisture) / (MAX_WETNESS-MIN_WETNESS)) * 100);
  }
}

bool postMessageToSlack(String msg)
{
  // first check the wifi status
  if (WiFi.status() != WL_CONNECTED) {  
    reconnect();
  }  
  
  HTTPClient https;
  Serial.println("Start the connection");
  if(https.begin(host, 443, webhookUrl, true, fingerprint)) {
      https.addHeader("Content-Type", "application/json");
      Serial.print("[HTTPS] posting\n");
      int httpCode = https.POST("{\"text\":\"" + msg + "\",\"username\": \"" + slack_username + "\",\"icon_url\": \"" + slack_icon_url + "\"}");
      if (httpCode > 0) {
        Serial.printf("[HTTPS] POST response: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] POST error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
  }
}
