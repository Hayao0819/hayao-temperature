#include <Arduino.h>
#include <DallasTemperature.h>
#include <ESPAsyncWebServer.h>
#include <OneWire.h>
#include <WiFi.h>

#include "const.h"

OneWire oneWire(7);
DallasTemperature sensors(&oneWire);

AsyncWebServer server(80);

float get_temp();

void setup() {
    // serial setup
    Serial.begin(9600);

    // wifi setup
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("connecting");
    }
    Serial.println(WiFi.localIP());

    // sensor setup
    sensors.setResolution(9);
    sensors.begin();

    // server setup
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(200, "text/plain", String(get_temp()));
    });

    server.begin();
}

float get_temp() {
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);
    Serial.print(temp);
    Serial.println("℃");
    return temp;
}

void loop() {
}
