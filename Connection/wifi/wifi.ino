#include <ESP8266WiFi.h>

String ssid = "ledzGO";
String psk = "password";

void setup(){
    Serial.begin(115200);
    Serial.println("LedzGo slave node start");
    
    Serial.println("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, psk);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
}

void loop(){

}
