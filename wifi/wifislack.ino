#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const String slack_icon_url = ":red_chili:";
const String slack_username = "Chiliplant";

const char* host = "hooks.slack.com";
// fingerprint of hooks.slack.com
const char* fingerprint = "C1 0D 53 49 D2 3E E5 2B A2 61 D5 9E 6F 99 0D 3D FD 8B B2 B3";
const char* webhookUrl = "/services/AAAAAAA/BBBBBB/cccccdddeeefff";


/*
 WIFI CONFIGURATION
 */
char SSID[] = "WLAN";
char pwd[] = "PASS";

void setup() {
  Serial.begin(9600);
  Serial.println();
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

  postMessageToSlack("Testing chili-esp8266");
}

void loop() {
  // put your main code here, to run repeatedly:
  // do nothing here just send the message on setup
}


bool postMessageToSlack(String msg)
{
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
