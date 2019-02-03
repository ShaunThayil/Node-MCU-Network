
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/*
 Disaster:
 Op1: Flood
 Op2:Earthquake
 Op3:Tsunami
 Op4:Cyclone

 Help Section:
 Op1:Evacuation 
 Op2:Injured
 Op3:Food
 Op4:Water
 Op5:Medicine
 
 */




#define LED D1
//SSID and Password to your ESP Access Point
const char* ssid = "test";
const char* password = "workchey";
int num=0;

String disaster[]={"Flood","Earthquake","Tsunami","Cyclone"};       //Set Of All Disasters
String aid[]={"Evacuation","Injury","Food","Water","Medicine"};     //Set Of All Aids
String disasterT="";                   //
String aidT="";
//int index;

ESP8266WebServer server(80); //Server on port 80


//Variable which contains the HTML Code to be renderd when the homepage is requested
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
 <marquee><h4>NEAREST SUPPLIES DROP &amp EVACUVATION POINT</h4></marquee>
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



// Display Home Page 
void handleRoot() {

 //Serial.println("You called root page");
 String homepage = MAIN_page; //Read HTML contents
 server.send(200, "text/html", homepage); //Send web page
  
 
}

//Helper Functions

void messageSender(){   //Open Message Sent Webpage
String messageSent="<center><h1>Message Sent</h1><br><a href=\"http://192.168.4.1\">Back</a></center>";
server.send(200, "text/html", messageSent); 
}

void setType(int index,int type {      //To set the content of the Data Pages
//Type 0 -Disaster
//Type 1 -Aid
String insert;
  if(type==0){
    insert=disaster[index];
    disasterT="<h1 align=\"Center\">"+insert+"</h1>";
  }
  else if(type==1){
    insert=aid[index];
    aidT="<h1 align=\"Center\">"+insert+"</h1>";
  }

}



//Disaster Setter
void ledOn(){    //Led Turns On when the source sends a request
  digitalWrite(D1,HIGH);
}
void disasterOp1() { 
  messageSender();
  ledOn();
  setType(0,0);
}

void disasterOp2() { 

messageSender();
ledOn();
setType(1,0);

}

void disasterOp3() { 

messageSender();
ledOn();
setType(2,0);
 
}

void disasterOp4() { 
 
messageSender();
ledOn();
setType(3,0);

}


//Aid Setter


void helpOp1(){
 
messageSender();
 setType(0,1);
 ledOn();
}

void helpOp2(){
messageSender();
 setType(1,1);
 ledOn();
 
}

void helpOp3(){
  
messageSender();
setType(2,1);
ledOn();
}


void helpOp4(){

messageSender();
setType(3,1);
ledOn();

}

void helpOp5(){

messageSender();
setType(4,1);
ledOn();
}

//Target Disaster Viewer
void ledOff(){       // LED turns off when the target accesses the webpage /DisasterType or /AidType
  digitalWrite(D1,LOW);
 
}
void distype(){
  server.send(200, "text/html", disasterT);
  ledOff();
   disasterT="";
}

void aidtype(){
    server.send(200, "text/html", aidT);
    ledOff();
    aidT="";
  
}


//SETUP
void setup(void){

  Serial.begin(9600);
  Serial.println("");
  pinMode(D1,OUTPUT);
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security

  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);

 //Home Page
  server.on("/", handleRoot);   

  //Disaster
  server.on("/Flood", disasterOp1); 
  server.on("/Earthquake", disasterOp2);
  server.on("/Tsunami", disasterOp3);
  server.on("/Cyclone", disasterOp4);

  //Help
  server.on("/Evacuation",helpOp1);
  server.on("/Injured",helpOp2);
  server.on("/Food",helpOp3);
  server.on("/Water",helpOp4);
  server.on("/Medicine",helpOp5);

  //Final Output
  server.on("/DisasterType",distype);
  server.on("/AidType",aidtype);

  //Disaster  View
  
  
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}


void loop(void){
  server.handleClient();          //Handle client requests
}
