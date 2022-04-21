/* 
{/////////////////////////////////////////////////////////////////}
Developed By OriginOfSouls{https://debajyotisarkarhome.github.io/}
{/////////////////////////////////////////////////////////////////}
Transmission Packet Defination :

{"Secret":"008c70392e3abfbd0fa47bbc2ed96aa99bd49e159727fcba0f2e6abeb3a9d601","Direction":"8","RotationCW":0,"RotationCCW":0,"Speed":"100"}

Direction Vector Index : 
  
 0 : Static
 1 : N
 2 : S
 3 : E
 4 : W
 5 : NE
 6 : NW
 7 : SE
 8 : SW

?????????????????????????????????????????????????????????????????????????
ERROR Codes : 
0001 : Auth Error

*/


#include <RH_ASK.h>
#include <SPI.h> 
#include "LittleFS.h"
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define secret "008c70392e3abfbd0fa47bbc2ed96aa99bd49e159727fcba0f2e6abeb3a9d601"

RH_ASK driver(2000,5,12,10,false);  // Data pin NodeMCU D6
char* ssid = "SSID";
char* password = "password";
AsyncWebServer server(80); 

void setup(){
  // put your setup code here, to run once:
  driver.init();
  Serial.begin(115200);
  if(!LittleFS.begin()){
            Serial.println("An Error has occurred while mounting LittleFS");
            return;
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });
  server.begin();
}



int drive(char transmissionBufer){
  int i,Direction,RotationCW,RotationCCW,Speed;
  DynamicJsonDocument transmissionPacket(1024);
  deserializeJson(transmissionPacket, transmissionBufer);
  Direction=transmissionPacket["Direction"];
  RotationCW=transmissionPacket["RotationCW"];
  RotationCCW=transmissionPacket["RotationCCW"];
}




void loop(){
//  uint8_t receiveBuffer[70];
//  uint8_t buflen = sizeof(receiveBuffer);
//  if (driver.recv(receiveBuffer, &buflen)){
//    Serial.println((char)buf[0]);
//  }
  
  
}
