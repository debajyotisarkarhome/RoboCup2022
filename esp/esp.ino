////////////////////////////////Created by OriginOfSouls{https://github.com/debajyotisarkarhome}//////////////////////////



// Import required libraries
#include <FS.h>
#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>

#define M11 16
#define M12 5
#define M21 4
#define M22 0
#define M31 2
#define M32 14
#define M41 12
#define M42 13
#define MS 15
#define servoPin 10

#define pwnMax 400
Servo myservo;  

const char* ssid = "ssid"; 
const char* password = "pass"; 

const int ledPin = 2;
String ledState;

AsyncWebServer server(80);


void forward(int sped){
  analogWrite(MS,sped);
  digitalWrite(M11,HIGH);
  digitalWrite(M12,LOW);
  digitalWrite(M21,HIGH);
  digitalWrite(M22,LOW);
  digitalWrite(M31,HIGH);
  digitalWrite(M32,LOW);
  digitalWrite(M41,HIGH);
  digitalWrite(M42,LOW);
}

void backward(int sped){
  analogWrite(MS,sped);
  digitalWrite(M11,LOW);
  digitalWrite(M12,HIGH);
  digitalWrite(M21,LOW);
  digitalWrite(M22,HIGH);
  digitalWrite(M31,LOW);
  digitalWrite(M32,HIGH);
  digitalWrite(M41,LOW);
  digitalWrite(M42,HIGH);
}
void right(int sped)
{
  analogWrite(MS,sped);
  digitalWrite(M11,HIGH);
  digitalWrite(M12,LOW);
  digitalWrite(M21,LOW);
  digitalWrite(M22,HIGH);
  digitalWrite(M31,LOW);
  digitalWrite(M32,HIGH);
  digitalWrite(M41,HIGH);
  digitalWrite(M42,LOW);
}
void left(int sped){
  analogWrite(MS,sped);
  digitalWrite(M11,LOW);
  digitalWrite(M12,HIGH);
  digitalWrite(M21,HIGH);
  digitalWrite(M22,LOW);
  digitalWrite(M31,HIGH);
  digitalWrite(M32,LOW);
  digitalWrite(M41,LOW);
  digitalWrite(M42,HIGH);
}

void cw(int sped){
  analogWrite(MS,sped);
  digitalWrite(M11,LOW);
  digitalWrite(M12,HIGH);
  digitalWrite(M21,HIGH);
  digitalWrite(M22,LOW);
  digitalWrite(M31,LOW);
  digitalWrite(M32,HIGH);
  digitalWrite(M41,HIGH);
  digitalWrite(M42,LOW);
}

void ccw(int sped){
  analogWrite(MS,sped);
  digitalWrite(M11,HIGH);
  digitalWrite(M12,LOW);
  digitalWrite(M21,LOW);
  digitalWrite(M22,HIGH);
  digitalWrite(M31,HIGH);
  digitalWrite(M32,LOW);
  digitalWrite(M41,LOW);
  digitalWrite(M42,HIGH);
}
 
void setup(){
  pinMode(M11,OUTPUT);
  pinMode(M12,OUTPUT);
  pinMode(M21,OUTPUT);
  pinMode(M22,OUTPUT);
  pinMode(M31,OUTPUT);
  pinMode(M32,OUTPUT);
  pinMode(M41,OUTPUT);
  pinMode(M42,OUTPUT);
  
  Serial.begin(115200);
  myservo.attach(servoPin);
  pinMode(ledPin, OUTPUT);

  // Initialize LittleFS
  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
  
  // Connect to Wi-Fi
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,password);
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
//  WiFi.begin(ssid,password);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(1000);
//    Serial.println("Connecting to WiFi..");
//  }
  // Print ESP32 Local IP Address

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html");
  });
  server.on("/drive",HTTP_GET, [](AsyncWebServerRequest *request){
    
    Serial.println(request->getParam(1)->value().toInt());
    if(request->getParam(0)->value()=="forward"){
      forward(request->getParam(1)->value().toInt());
      request->send(200);
    }
    if(request->getParam(0)->value()=="backward"){
      backward(request->getParam(1)->value().toInt());
      request->send(200);
    }
    if(request->getParam(0)->value()=="left"){
      left(request->getParam(1)->value().toInt());
      request->send(200);
    }
    if(request->getParam(0)->value()=="right"){
      right(request->getParam(1)->value().toInt());
      request->send(200);
    }
    if(request->getParam(0)->value()=="cw"){
      cw(request->getParam(1)->value().toInt());
      request->send(200);
    }
    if(request->getParam(0)->value()=="ccw"){
      ccw(request->getParam(1)->value().toInt());
      request->send(200);
    }
    if(request->getParam(0)->value()=="flap"){
      myservo.write(0);
      delay(500);
      myservo.write(90);
      delay(500);
      myservo.write(180);
      delay(500);
    }
  });
  server.begin();
}
 
void loop(){
  
}
