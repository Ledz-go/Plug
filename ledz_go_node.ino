#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESPDMX.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>

String ssid = "ledzGO";
String psk = "password";

WiFiUDP Udp;
IPAddress Master_IP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);
IPAddress Broadcast(192,168,4,255);
unsigned int localPort = 8888;


char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
DMXESPSerial dmx;
int nodeMode=1;
void treatJson(DynamicJsonDocument json){
    //exemple Command:{"Version":"1.0","Data":{"Type":"Command","Channels":[1,2,3,4]}}
    if(json["Data"]["Type"]=="Command"){
      Serial.println("Lum Mode");
      int RGB[]={json["Data"]["Channels"][0],json["Data"]["Channels"][1],json["Data"]["Channels"][2]};
      dmx.write(1,RGB[0]);
      dmx.write(2,RGB[1]);
      dmx.write(3,RGB[2]);
      dmx.update();
    }else{
      Serial.println("Wrong Type of Json");
    }
}
void setup()
{
  Serial.begin(9600);
  Serial.println("Begin"); 
  
  WiFi.begin(ssid, psk);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Udp.begin(localPort);
  dmx.init(512);
}

void loop() {
  dmx.update();
  if(nodeMode==1){
    Udp.beginPacket(Master_IP, localPort);
    uint8_t macAddr[6];
    WiFi.macAddress(macAddr);
    char address[30];
    Serial.println(WiFi.localIP().toString().c_str());
    sprintf(address,"%s %s",WiFi.localIP().toString().c_str(),WiFi.macAddress().c_str());
    Udp.println(address);
    Udp.endPacket();
    nodeMode=0;
  }else{
    int packetSize = Udp.parsePacket();
    if (packetSize) {
      Serial.println("RunMode");
      int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
      packetBuffer[n] = 0;
      Serial.println(packetBuffer);
      DynamicJsonDocument receivedData(1024);
      deserializeJson(receivedData,packetBuffer);
      treatJson(receivedData);
    }
  }
}
