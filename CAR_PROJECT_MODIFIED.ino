//Bluetooth
#include<SoftwareSerial.h>
int ledpin=2;
int ledpin1=8;
const int txpin=1;
const int rxpin=0;
String readmsg;

SoftwareSerial BT(rxpin,txpin);

//Temperature sensor
const int sensor=A0;
float tempc;
float tempf; 
float out;

//Motor rotation
  #define enA 6
  #define enB 5
  #define in1 4
  #define in2 7
  #define in3 11
  #define in4 12
  
  
//ultrasonic sensor
#define trigpin 9
#define echopin 10
#define switchpin 3
long a;
int distance;

//relay
 int relaypin=13;

 //ldr
#define ldrpin A5


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(trigpin,OUTPUT);
  pinMode(switchpin,INPUT);
  pinMode(sensor,INPUT);
  pinMode(ledpin,OUTPUT);
  pinMode(relaypin,OUTPUT);
  pinMode(ldrpin,INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(enA, 255);
  analogWrite(enB, 255);
 int B;
  B=digitalRead(switchpin);
  if(B==HIGH){
  // put your main code here, to run repeatedly:
long a;
long distance;

digitalWrite(trigpin,LOW);
delayMicroseconds(2);

digitalWrite(trigpin,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin,LOW);
a=pulseIn(echopin,HIGH);
distance=(a*0.0321)/2;
if(distance<100)
{
 analogWrite(enA, 127);
 analogWrite(enB, 127);
  digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 Serial.print("Obstacle detected @ 100m");
delay(500);
Serial.println(distance);
Serial.println("cm");
delay(500);
  }
  }
  else
  {
   analogWrite(enA, 255);
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 analogWrite(enB, 255);
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
    }
   

  

  //to detect hump and pathhole
 /* {
long a;
long distance;

digitalWrite(trigpin,LOW);
delayMicroseconds(2);

digitalWrite(trigpin,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin,LOW);
a=pulseIn(echopin,HIGH);
distance=(a*0.0321)/2;
if(distance<20)
{
 analogWrite(enA, 100);
  digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 analogWrite(enB, 100);
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 Serial.println("Warning:Hump detected!");
delay(500);
  
  }
  else if((distance>20)&&(distance<30))
  {
   analogWrite(enA, 100);
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 analogWrite(enB, 100);
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 Serial.println("Warning:path hole detected!");
delay(500);
  
    }
else
    {
   analogWrite(enA, 255);
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 analogWrite(enB, 255);
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
    }
   
   
Serial.print(distance);
Serial.println("cm");
delay(500);
  
}*/

//temperature sensor
{
out=analogRead(sensor);
 out=(out*500)/1023;
 tempc=out;//temperature in celsius
 tempf=(out*1.8)+32;//temperature in fahrenheit
 if(out>=29){
 Serial.println("AC ON");
  digitalWrite(ledpin,HIGH);
 delay(500);
 }
 else{
  Serial.println("AC OFF");
  digitalWrite(ledpin,LOW);
 delay(500);
  }
 
 
 Serial.print("Temperature degree Celsius=");
 Serial.println(tempc);

 delay(500);
 //Serial.print("Temperature degree Fahrenheit=");
 //Serial.println(tempf);

  Serial.print("\n");
  // delay(1000);
 
}

//ignition ON and OFF
 
 while(BT.available()){
  delay(10);
   char c=BT.read();
  readmsg+=c;
  }
  if(readmsg.length()>0){
if(readmsg=="*on#"){
  
      Serial.println("Ignition ON mode");
      delay(100);
      digitalWrite(relaypin,LOW);
    }
    else if(readmsg=="*stop#"){
   
    Serial.println("Ignition OFF mode");
    delay(100);
      digitalWrite(relaypin,HIGH);
   }
   
   delay(600);
   Serial.println(readmsg);
   readmsg="";

  }
   
   //ldr
   
  int ldrStatus= analogRead(ldrpin);

  if(ldrStatus>=40){

    digitalWrite(ledpin1,HIGH);

    Serial.print("It's dark,turn ON the led=");

    Serial.println(ldrStatus);

    delay(1000);

  }

  else{

    digitalWrite(ledpin1,LOW);

    Serial.print("It's bright,turn off led=");

    Serial.println(ldrStatus);

    delay(1000);

  }
}
  
