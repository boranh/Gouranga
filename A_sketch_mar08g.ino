sketch_mar08g#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
//#include <FirebaseArduino.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "b1X0GvRCzgVkVFmdqapDojAXO9jVxzWP";
// Set these to run example.
//#define FIREBASE_HOST "getvalue-iot.firebaseio.com"
//#define FIREBASE_AUTH "S5Gdr6ySjOkPdBGlZgnUEWOEh64wb60kbkzkOXoa"
char ssid[] = "OnePlus7T";
char pass[] = "12345678ct";

String myString;
char rdata; // received charactors

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);


  // Setup a function to be called every second
  //timer.setInterval(1000L, sendSensor1);
  
  //Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

   //Firebase.setString("Variable/Value","Gouranga");
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  //timer.run(); // Initiates SimpleTimer
  
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString + rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {
     Serial.println(myString); 
  // Serial.println("Sucess");
  // new code
  String l = getValue(myString, ',', 0);
  String m = getValue(myString, ',', 1);
  String n = getValue(myString, ',', 2);
  String o = getValue(myString, ',', 3);
  
int  MQ6 = l.toInt();
int  MQ9 = m.toInt();
int  Temp = n.toInt();
int  FanSpeed = o.toInt();
myString = "";


  Blynk.virtualWrite(V2, MQ6);
  Blynk.virtualWrite(V3, MQ9);
  Blynk.virtualWrite(V4, Temp);
  Blynk.virtualWrite(V5, FanSpeed);
  
//  Firebase.setFloat("MQ6", MQ6);
//  Firebase.setFloat("MQ9", MQ9);
//  Firebase.setFloat("Temp", Temp);
//  Firebase.setFloat("FanSpeed", FanSpeed);
  } 
 }
} 
  
