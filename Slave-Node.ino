#include <ESP8266WiFi.h>
#include <ESPDMX.h>

// Wifi vars
String ssid = "ledzGO";
String psk = "password";

// DMX vars
DMXESPSerial dmx;

void setup(){
    Serial.begin(115200);
    Serial.println("LedzGo slave node start");
    
    // Wifi setup
    Serial.println("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, psk);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");

    // DMX setup
    dmx.init(512);

    // To use :
    // dmx.write(channel, value) for on off channel
    // dmx.write() for update dmx bus
}

void loop(){

}
