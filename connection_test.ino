/*
 * Hello world web server
 * circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//SSID and Password to your ESP Access Point
const char* ssid = "test";
const char* password = "workchey";
int num=0;

ESP8266WebServer server(80); //Server on port 80
#define LED D1
//==============================================================
//     This rutine is exicuted when you open its IP in browser
//==============================================================

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>WiFi LED on off demo: 1</h1><br>
Click to turn <a href="op1">Flood</a><br>
Click to turn <a href="op2">Earthquake</a><br>
<hr>
<a href="back">Reset</a>
</center>
 
</body>
</html>
)=====";
void handleRoot() {
  if(num==0){
 //Serial.println("You called root page");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
  }
  else if(num==1){
    server.send(200,"text/html","<h1>Flood</h1>");
    num=0;
    }

 else if(num==2){
    server.send(200,"text/html","<h1>EarthQuake</h1>");
    num=0;
 }
}

void resetNum(){
  num=0;
}

void oneOp() { 
 Serial.println("LED on page");
 //digitalWrite(LED,HIGH); //LED is connected in reverse
 server.send(200, "text/html", "1"); //Send ADC value only to client ajax request
 num=1;
}
 
void twoOp() { 
 Serial.println("LED off page");
 //digitalWrite(LED,LOW); //LED off
 server.send(200, "text/html", "2"); //Send ADC value only to client ajax request
 num=2;
}

//===============================================================
//                  SETUP
//===============================================================
void setup(void){
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  Serial.println("");
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security

  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
 
  server.on("/", handleRoot);      //Which routine to handle at root location
     //Which routine to handle at root location. This is display page
  server.on("/op1", oneOp); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/op2", twoOp);
  server.on("/back",resetNum); //To Reset Num Variable

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//===============================================================
//                     LOOP
//===============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
