This code is for the Ardunio board

//Final MAl
/*
*/
#include <SoftwareSerial.h>
SoftwareSerial nodemcu(0,1);
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
int RelayBulb = 9;
int MQ6 = A0;
int MQ9 = A1;
int tempPin = A2; // the output pin of LM35
int fan = 10;     // the pin where fan is
int tempMin = 30; // the temperature to start the fan 0%
int tempMax = 60; // the maximum temperature when fan is at 100%
int fanSpeed;
int fanLCD;
String cdata ="";
int temp;
int gasSensor1;
int gasSensor2;
//LM35, fan, LM35



void setup() {
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  pinMode(fan, OUTPUT);
  pinMode(tempPin, INPUT);
  
   lcd.setCursor(0, 0);
  lcd.print("Calibrating");
    for(int i = 0; i <10; i++){
      if (i==4)
      {
         lcd.setCursor(0, 1);
         lcd.print(".");
        }
       else  lcd.print(".");
      delay(500);
      }
    lcd.setCursor(5, 1);
    lcd.print("done");
    delay(1000);
    lcd.clear(); 
    lcd.setCursor(1, 0);
    lcd.print("SENSOR ACTIVE");
    delay(1500);
    lcd.clear();
}
  

void loop() {

  p1slot1();
  SendData();
  delay(1400);
  lcd.clear();
  SendData();
  
  p1slot2();
  SendData();
  delay(1400);
  lcd.clear();
  SendData();
  
  p1slot3();

  plslot4();
  SendData();
  delay(1400);
  lcd.clear();
  SendData();
}


void SendData() {
  
  cdata = cdata + gasSensor1 +"," + gasSensor2 + ","+ temp + ","+ fanSpeed + ","; // comma will be used a delimeter
  Serial.println(cdata); 
  nodemcu.println(cdata);
  cdata = "";  
}











void p1slot1() {
  gasSensor1 = analogRead(MQ6);
  if (gasSensor1 > 350)
  {
     digitalWrite(RelayBulb,HIGH);
     lcd.setCursor(0, 0);
     lcd.print("MQ6 (PPM): ");
     lcd.print(gasSensor1);
     //Serial.print(gasSensor1);
     //Serial.print("\t");
     lcd.setCursor(0, 1);
     //Serial.println("Gas is Detected");   
     lcd.print("Gas is Detected");
  }
  else if (gasSensor1 < 350)
  {
     digitalWrite(RelayBulb,LOW);
     lcd.setCursor(0, 0);
     lcd.print("MQ6 (PPM) : ");
     lcd.print(gasSensor1);
     //Serial.print(gasSensor1);
     //Serial.print("\t");
     lcd.setCursor(0, 1);
     //Serial.println("No Gas"); 
     lcd.print("No Gas");
  }
}


void p1slot2() {
  gasSensor2 = analogRead(MQ9);
  if (gasSensor2 > 350)
  {
     digitalWrite(RelayBulb,HIGH);
     lcd.setCursor(0, 0);
     lcd.print("MQ9 (PPM): ");
     lcd.print(gasSensor2);
     //Serial.print(gasSensor2);
     //Serial.print("\t");
     lcd.setCursor(0, 1);
     //Serial.println("Gas is Detected");   
     lcd.print("Gas is Detected");  
  }
  else if (gasSensor2 < 350)
  {
     digitalWrite(RelayBulb,LOW);
     lcd.setCursor(0, 0);
     lcd.print("MQ9 (PPM): ");
     lcd.print(gasSensor2);
     //Serial.print(gasSensor2);
     //Serial.print("\t");
     lcd.setCursor(0, 1);
     //Serial.println("No Gas"); 
     lcd.print("No Gas");   
  }
}


void p1slot3() { /////bujibo ase day bhal ke sah good nyt
  
  temp = analogRead(tempPin);
  //Serial.print( temp );
  
  if(temp < tempMin) {                              //tempMin = 30
    fanSpeed = 0;                                   // fan is not spinning
    analogWrite(fan, fanSpeed);
    fanLCD=0;
    digitalWrite(fan, LOW);  
  }
  
  else if((temp >= tempMin) && (temp <= tempMax)) {
    fanSpeed = temp;                                //map(temp, tempMin, tempMax, 0, 100); // the actual speed of fan//map(temp, tempMin, tempMax, 32, 255);
    fanSpeed=1.5*fanSpeed;
    fanLCD = map(temp, tempMin, tempMax, 0, 100);   // speed of fan to display on LCD100
    analogWrite(fan, fanSpeed);                     // spin the fan at the fanSpeed speed
    }
}

void plslot4() {
   temp = (5.0 * temp * 100.0)/1024.0;  //convert the analog data to temperature
   
  lcd.setCursor(0, 0);
  lcd.print("TEMP: ");
  lcd.print(temp);
  //Serial.print(temp);
  //Serial.print("\t");
  lcd.setCursor(0, 1);
  lcd.print("FANS: ");
  lcd.print(fanLCD);
  //Serial.println(fanLCD); 
  lcd.print("%"); 
  }

