/*******************************************************************
    A sample project for making a HTTP/HTTPS GET request on an ESP8266
    and parsing it from JSON

    It will connect to the given request, parse the JSON and print the 
    body to serial monitor

    Parts:
    D1 Mini ESP8266 * - http://s.click.aliexpress.com/e/uzFUnIe

 *  * = Affilate

    If you find what I do usefuland would like to support me,
    please consider becoming a sponsor on Github
    https://github.com/sponsors/witnessmenow/


    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Tindie: https://www.tindie.com/stores/brianlough/
    Twitter: https://twitter.com/witnessmenow
 *******************************************************************/


// ----------------------------
// Standard Libraries
// ----------------------------

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <ArduinoJson.h>
// Library used for parsing Json from the API responses

// Search for "Arduino Json" in the Arduino Library manager
// https://github.com/bblanchon/ArduinoJson

//------- Replace the following! ------
char ssid[] = "CloudWifi-617";       // Wifi network name
char password[] = "";  // No password

// For Non-HTTPS requests
// WiFiClient client;

// For HTTPS requests
WiFiClientSecure client;


// Base of the URL
#define TEST_HOST "https://api.open-meteo.com/v1/forecast?latitude=43.4668&longitude=-80.5164&hourly=rain"

#define TEST_HOST_FINGERPRINT "3B:D7:94:40:39:18:85:57:3A:00:EB:52:2D:BB:BD:67:8E:19:77:38
// The finger print will change every few months.


void setup() {

  Serial.begin(115200);

  // Connect to the WiFI
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  //--------

  // Check the fingerprint
  client.setFingerprint(TEST_HOST_FINGERPRINT);

 // makeHTTPRequest();
}



void loop() {

}