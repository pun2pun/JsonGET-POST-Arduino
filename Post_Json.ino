//Post Json 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);                            //Serial connection
  WiFi.begin("UU", "1212312121");   //WiFi connection
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
 }
} 

void loop() {
  int sensor_value = 45;
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
  String json = "{\"sensor\":\"gps\",\"value\":\""+ String(sensor_value) +"\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
  DynamicJsonBuffer  jsonBuffer;
  char postMessage[300]; 
  JsonObject& root = jsonBuffer.createObject();
  JsonObject& Jarray = jsonBuffer.parseObject(json); 
  root["name"] = "lll";
  root["content"] = Jarray;
  root.printTo(postMessage,sizeof(postMessage));
  Serial.print(postMessage);
  
//----------------------------------------------------------
         HTTPClient http;
         http.begin("http://iot.data.ubu.ac.th/api/save" );      
         http.addHeader("Content-Type", "application/json");
         int httpCode = http.POST(postMessage);

    String payload = http.getString();                                        //Get the response payload
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    http.end();  //Close connection
  }
 else {
    Serial.println("Error in WiFi connection");
  }
  delay(3000);  //Send a request every 30 seconds
}
