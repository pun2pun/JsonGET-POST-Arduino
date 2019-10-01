//Get Json
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#define ON LOW
#define OFF HIGH
// WiFi Parameters
const char* ssid = "HUAWEI Y6II";
const char* password = "bbbbbbbb";
int R = D1;
String email ;
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(R,OUTPUT);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void loop() {
  // Check WiFi Status
  Serial.println(WiFi.status());
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("http://iot.data.ubu.ac.th/api/get/lated/SCADAProject");
    int httpCode = http.GET();
    //Check the returning code                                                                  
    if (httpCode > 0) {
      // Get the request response payload
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
     // const size_t bufferSize_2 = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      int id = root["id"]; // 1
      const char* names = root["name"]; // "Leanne Graham"
      String username = root["content"]; // "Bret"
      String email = root["content"]["Lamp 1"]; // "Sincere@april.biz"
      Serial.print("Name:");
      Serial.println(names);
      Serial.print("Username:");
      Serial.println(username);
      Serial.print("Email:"); 
      Serial.println(email);
      //Serial.println();
      if (email == "1"){
      digitalWrite(R,ON);
      Serial.println("ON");
      }
      else 
      {digitalWrite(R,OFF);
      Serial.println("OFF");} 
      // Delay
    }
    http.end();   //Close connection
  }

  delay(10);
}

