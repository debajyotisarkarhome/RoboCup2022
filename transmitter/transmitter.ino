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

*/

#include <RH_ASK.h>
#include <SPI.h>
#include <ArduinoJson.h>

#define joyX A0
#define joyY A1
#define leftStickButton 7
#define rightStickButton 6
#define secret "008c70392e3abfbd0fa47bbc2ed96aa99bd49e159727fcba0f2e6abeb3a9d601"

RH_ASK driver;

void setup() {
  pinMode(leftStickButton,INPUT);
  pinMode(rightStickButton,INPUT);
  Serial.begin(9600);
  driver.init();
}

void loop() {
  char transmissionBuffer[138];
  DynamicJsonDocument transmissionPacket(138);
  transmissionPacket["Secret"]=secret;
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  if(xValue>611 and yValue<611 and yValue>411)
    transmissionPacket["Direction"]="1";
  else if(xValue<411 and yValue>411 and yValue<611)
    transmissionPacket["Direction"]="2";
  else if(xValue>411 and xValue<611 and yValue>611)
    transmissionPacket["Direction"]="3";
  else if(xValue>411 and xValue<611 and yValue<411)
    transmissionPacket["Direction"]="4";
  else if(xValue>611 and yValue>611)
    transmissionPacket["Direction"]="5";
  else if(xValue>611 and yValue<411)
    transmissionPacket["Direction"]="6";
  else if(xValue<411 and yValue>611)
    transmissionPacket["Direction"]="7";
  else if(xValue<411 and yValue<411)
    transmissionPacket["Direction"]="8";
  else
    transmissionPacket["Direction"]="0";
  

  //    Rotation Vector Control

  transmissionPacket["RotationCW"]=digitalRead(leftStickButton);
  transmissionPacket["RotationCCW"]=digitalRead(rightStickButton);
  transmissionPacket["Speed"]="100";


  serializeJson(transmissionPacket,transmissionBuffer);
  driver.send((uint8_t*)transmissionBuffer,strlen(transmissionBuffer));
  driver.waitPacketSent();
  delay(100);
}
