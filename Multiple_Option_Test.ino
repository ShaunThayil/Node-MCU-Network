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
//#define LED D1
//==============================================================
//     This rutine is exicuted when you open its IP in browser
//==============================================================

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>DISASTER RESCUE</h1><br>
<a href="Flood">Flood</a><br>
 <a href="Earthquake">Earthquake</a><br>
 <a href="Tsunami">Tsunami</a><br>
 <a href="Cyclone">Cyclone</a><br>
 <marquee><h4>SUPPLIES DROP</h4></marquee>
 <h1>Type Of Distress</h1>
 <a href="Evacuation">Need Evacuation</a><br>
 <a href="Injured">Injured People</a><br>
 <a href="Food">No Food</a><br>
 <a href="Water">No Water</a><br>
 <a href="Medicine">No Medicines</a><br>
 
<hr>

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
    server.send(200,"text/html","<p>Flood</p>");
    //num=0;
    }

 else if(num==2){
    server.send(200,"text/html","<p>EarthQuake</p>");
   // num=0;
 }

 else if(num==3){
  server.send(200,"text/html","Tsunami");
   // num=0;
 }

 else if(num==4){
  server.send(200,"text/html","Cyclone");
   // num=0;
 }

else if(num==5){
  server.send(200,"text/html","Need Evacuation!!");
    //num=0;
}

else if(num==6){
 server.send(200,"text/html","Injured People!!");
  //  num=0;
}

else if(num==7){
 server.send(200,"text/html","No Food!!");
  //  num=0;
}
else if(num==8){
  server.send(200, "text/html", "No Water"); 
 // num=0;
}

else if(num==9){
  server.send(200, "text/html", "No Medicines"); 
  //num=0;
}

num=0;
}



void disasterOp1() { 
// Serial.println("LED on page");
 //digitalWrite(LED,HIGH); //LED is connected in reverse
 server.send(200, "text/html", "Flood"); //Send ADC value only to client ajax request
 num=1;
}
 
void disasterOp2() { 
 //Serial.println("LED off page");
 //digitalWrite(LED,LOW); //LED off
 server.send(200, "text/html", "EarthQuake"); //Send ADC value only to client ajax request
 num=2;
}

void disasterOp3() { 
 //Serial.println("LED off page");
 //digitalWrite(LED,LOW); //LED off
 server.send(200, "text/html", "Tsunami"); //Send ADC value only to client ajax request
 num=3;
}

void disasterOp4() { 
 //Serial.println("LED off page");
 //digitalWrite(LED,LOW); //LED off
 server.send(200, "text/html", "Cyclone"); //Send ADC value only to client ajax request
 num=4;
}

void helpOp1(){
  server.send(200, "text/html", "Need Evacuation!!"); //Send ADC value only to client ajax request
 num=5;
}

void helpOp2(){
  server.send(200, "text/html", "Injured People!!"); //Send ADC value only to client ajax request
 num=6;
}

void helpOp3(){
  server.send(200, "text/html", "No Food!!"); //Send ADC value only to client ajax request
 num=7;
}


void helpOp4(){
  server.send(200, "text/html", "No Water"); //Send ADC value only to client ajax request
 num=8;
}

void helpOp5(){
   server.send(200, "text/html", "No Medicines");
   num=9;
}


//===============================================================
//                  SETUP
//===============================================================
void setup(void){
  //pinMode(LED,OUTPUT);
  Serial.begin(9600);
  Serial.println("");
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security

  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
 
  server.on("/", handleRoot);      
  server.on("/Flood", disasterOp1); 
  server.on("/Earthquake", disasterOp2);
  server.on("/Tsunami", disasterOp3);
  server.on("/Cyclone", disasterOp4);
  server.on("/Evacuation",helpOp1);
  server.on("/Injured",helpOp2);
  server.on("/Food",helpOp3);
  server.on("/Water",helpOp4);
  server.on("/Medicine",helpOp5);
  
  
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//===============================================================
//                     LOOP
//===============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
