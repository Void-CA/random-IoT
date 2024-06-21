#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Ari";
const char* password = "12345678";
const char* serverUrl = "http://192.168.72.2:5000/receive_data";

const int sensorPin = A0;

WiFiClient client;

void setup() {
    Serial.begin(9600);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi!");
}

void loop() {
    int sensorValue = analogRead(sensorPin);
    Serial.print("Sensor value: ");
    Serial.println(sensorValue);

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        Serial.print("Connecting to server: ");
        Serial.println(serverUrl);

        http.begin(client, serverUrl);
        http.addHeader("Content-Type", "application/json");

        String jsonData = "{\"sensor_value\":" + String(sensorValue) + "}";
        Serial.print("JSON data: ");
        Serial.println(jsonData);

        int httpResponseCode = http.POST(jsonData);

        if (httpResponseCode > 0) {
            Serial.print("HTTP response code: ");
            Serial.println(httpResponseCode);
            Serial.println("Data sent successfully");
        } else {
            Serial.print("HTTP error code: ");
            Serial.println(httpResponseCode);
            Serial.println("Error sending data");
        }

        http.end();
    }

}
