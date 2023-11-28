#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WiFiClient client;
HTTPClient http;
String apiEndPoint = "https://api.open-meteo.com/v1/forecast?latitude=YOUR_LATITUDE&longitude=YOUR_LONGITUDE&hourly=precipitation_probability,precipitation_amount";
Servo myservo;  // create servo object to control a servo

void setup() {
  // Initialization code here
  // Setup serial communication, sensors, etc. if needed
  Serial.begin(115200); 
  myservo.attach(9);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {

  // CONNECT TO WIFI
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(client, apiEndPoint);

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);

      // Parse JSON
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);

      float precipitation_probability = doc["hourly"]["precipitation_probability"][0]; // Get the first hour's data
      float precipitation_amount = doc["hourly"]["precipitation_amount"][0];

      // Check precipitation probability
      if (precipitation_probability > 75) {
        // Check precipitation amount
        if (precipitation_amount > 2) {
          // Don't water
          // Add code to stop or not start the watering system
        } else {
          // Water for 5 minutes
          // Add code to start the watering system
          waterFor(5); // Assuming you have a function to handle the watering
        }

    } else {
      Serial.println("Error in HTTP request");
    }

    http.end();
  } else {
    Serial.println("Disconnected from WiFi");
  }

  delay(10000); // Delay to prevent constant looping

  }
  // If additional conditions are needed, add below
}

// Function to handle watering for a specified number of minutes
void waterFor(int minutes) {
// Turn the servo to 90 degrees to open the valve
  myservo.write(90); 
  delay(1000); // Wait for 1 second

  // Wait for the specified duration to water
  delay(minutes * 60000); // Convert ms to mins

  // Return the servo to 0 degrees to close the valve
  myservo.write(0);
  delay(1000); // Wait for 1 second to ensure the servo has reached the position
}
