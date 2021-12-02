#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
//maintenant tout est en Serial et on va le remplacer après
void treatJson(DynamicJsonDocument json){
  //exemple Command:{"Version":"1.0","Data":{"Type":"Command","Channels":[1,2,3,4]}}
  //exemple Discovery:{"Version":"1.0","Data":{"Type":"Discovery"}
  if(json["Data"]["Type"]=="Discovery"){
      Serial.println("Discovery Mode");
    }else if(json["Data"]["Type"]=="Command"){
      Serial.println("Lum Mode");
      int RGB[]={json["Data"]["Channels"][0],json["Data"]["Channels"][1],json["Data"]["Channels"][2],json["Data"]["Channels"][3]};
      Serial.println(RGB[0]);
      Serial.println(RGB[1]);
      Serial.println(RGB[2]);
      Serial.println(RGB[3]);
    }else{
      Serial.println("Wrong Type of Json");
    }
}
void setup()
{
  Serial.begin(115200);  
}

void loop() {
  //maintenant j'ai mis Serial mais ici ça devais remplacé par le socket
  while(Serial.available()){
    String read;
    DynamicJsonDocument json(1024);
    read=Serial.readString();
    deserializeJson(json,read);
    treatJson(json);
  }
  
}
