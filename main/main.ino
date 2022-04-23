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

//Pin Defination

#define M11 0
#define M12 1
#define M21 3
#define M22 4
#define M31 5
#define M32 6
#define M41 7
#define M42 8
#define M1S A0
#define M2S A1
#define M3S A2
#define M4S A3

#define radioPin 9

#define pwnMax 400




RH_ASK driver(2000,5,12,radioPin,false);  // Data pin NodeMCU D6
char* ssid = "SSID";
char* password = "password";
AsyncWebServer server(80); 

void setup(){
  // put your setup code here, to run once:
  for(int i=0;i<10;i++){
    pinMode(i,OUTPUT);
  }
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
  Speed=transmissionPacket["Speed"];
  if Speed>pwnMax:      //RPM Locked at designated PWM 
    Speed=pwmMAx;
  switch(Direction){
    case 0:
      break;
    case 1:
      digitalWrite(M11,HIGH);
      digitalWrite(M12,LOW);
      digitalWrite(M21,HIGH);
      digitalWrite(M22,LOW);
      digitalWrite(M31,HIGH);
      digitalWrite(M32,LOW);
      digitalWrite(M41,HIGH);
      digitalWrite(M42,LOW);
    case 2;
      digitalWrite(M11,LOW);
      digitalWrite(M12,HIGH);
      digitalWrite(M21,LOW);
      digitalWrite(M22,HIGH);
      digitalWrite(M31,LOW);
      digitalWrite(M32,HIGH);
      digitalWrite(M41,LOW);
      digitalWrite(M42,HIGH);
    case 3:
      digitalWrite(M11,HIGH);
      digitalWrite(M12,LOW);
      digitalWrite(M21,LOW);
      digitalWrite(M22,HIGH);
      digitalWrite(M31,LOW);
      digitalWrite(M32,HIGH);
      digitalWrite(M41,HIGH);
      digitalWrite(M42,LOW);
    case 4:
      digitalWrite(M11,LOW);
      digitalWrite(M12,HIGH);
      digitalWrite(M21,HIGH);
      digitalWrite(M22,LOW);
      digitalWrite(M31,HIGH);
      digitalWrite(M32,LOW);
      digitalWrite(M41,LOW);
      digitalWrite(M42,HIGH);
  }
}




void loop(){
//  uint8_t receiveBuffer[70];
//  uint8_t buflen = sizeof(receiveBuffer);
//  if (driver.recv(receiveBuffer, &buflen)){
//    Serial.println((char)buf[0]);
//  }
  
  
}
