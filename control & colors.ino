#include <Servo.h>
#include <SoftwareSerial.h>
#include<MD_TCS230.h> 
#include<FreqCount.h> 
#include<EEPROM.h>
#define S0 6
#define S1 5
#define S2 4
#define S3 7
#define sensorOut 2
int pangb=145,pangh=125,pangl=135;
// Stores frequency read by the photodiodes
int r= 0,colo;
int g= 0;
int b= 0;

int obred,obblue,obgreen ;
int bb=145,h=125,l=135,gg=92;
Servo base,forward,tolift,gripp;
char (c);

SoftwareSerial BT(0, 1);
//////////////////////
int check(int ang,int minn,int maxx){
  if (ang>maxx) ang=maxx;
  else if (ang<minn) ang=minn;
  else {ang=ang;}
  return ang;
}

void setup() {
  base.attach(3);
  forward.attach(9);
  tolift.attach(10);
  gripp.attach(11);
  delay(200);
  bs(bb);
  gripp.write(gg);
  li(h);
  li(l);
  Serial.write("Ready");

  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  // Begins serial communication 
  Serial.begin(9600);
  BT.begin(9600);
}
void loop() {
  
if (BT.available()>0){c=BT.read();}
switch(c){
  case 'a': bb=bb+5;  break;
  case 'b': bb=bb-5; break;
  case 'c': l=l+5;  break;
  case 'd': l=l-5;  break;
  case 'e': h=h+5;  break;
  case 'f': h=h-5;  break; 
  case 'g': gg=gg+5;  break;
  case 'h': gg=gg-5;  break;
  case 's': gg=92;  bb=145;h=120;l=135; break; //task 2
 // case 's': gg=92;  bb=90;h=120;l=135; break;  //task 1
  case 'q':trajgreen();
  case 'p' :
    red();
    green();
    blue();
    if(b<r && b<g){
      Serial.println("-BLUE DETECTED");
      delay(500);
      trajblue();
      obblue =1;
      colo=1; 
    }
    else if (r<g&& r<b){
      Serial.println("-RED DETECTED");
       delay(500);
      obred = 1 ;
      colo=2;   
      trajred();
    }
  else 
    {
      Serial.println("-GREEN DETECTED");
       delay(500);
      obgreen = 1 ;
      colo=3;    
      trajgreen();
    }} 
   // if (BT.available()>0 ) c=BT.read()=='q';
Serial.println(c);
Serial.println(bb);
Serial.println(l);
Serial.println(h);
Serial.println(gg);

bb=check(bb,5,175);
bs(bb);
//delay(10);

l=check (l,30,175);
li(l);
//delay(10);

h=check(h,100,175);
hi(h);
//delay(10);

gg=check(gg,92,160);
gripp.write(gg);
//delay(10);
c='o';

}
void lift(){ // common for the 3 colors w three shapes
  bs(150);
  delay(200);
  li(103); // tehbett
    delay(200);
  //delay(500);
  gripp.write(140);//open the gripp
  // delay(500);
  hi(125); //move forward
  //forward.write(125);
    delay(200);
      li(66); // tehbett
    delay(200);
    hi(160); //move forward
    delay(200);
  delay(500);
  gripp.write(95);//close the gripp w yrfed object de preference x))
  // delay(500);
  li(155); //ytele3 the object pin 10
  //delay(500);
}

void trajgreen(){
 lift();
 delay(500);
 Serial.println("hhhhh");
  bs(60);

//dor l base
 
  li(110); //move up  
  hi(100);//avancer
 // forward.write(125);
 delay(10);
  gg=140;
  delay(500);
  gripp.write(gg);//open the gripp
}

void trajred (){
  lift();
  delay(500);
  bs(85);
    
  li(110); //move up
  //hi(135);//avancer
    forward.write(127);
  //dor l base with a different angle nbedlo ghir hadi

  delay(500);
  gg=140;
  gripp.write(gg);//open the gripp

}

void trajblue(){
 lift();
 delay(500);
   bs(20);
  
  li(110); //move up 
    hi(133);//avancer
      forward.write(130);
//dor l base with another angle 
 
  delay(500);
  gg=140;
  gripp.write(gg);//open the gripp
}


void red(){
   // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
 // Reading the output frequency
  r = pulseIn(sensorOut, LOW);
 // Printing the RED (R) value
  Serial.print("R=");
  Serial.print(r);
  Serial.print(" ");
  delay(100);
}
void green(){
   // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
 // Reading the output frequency
  g = pulseIn(sensorOut, LOW);  
 // Printing the GREEN (G) value  
  Serial.print("G=");
  Serial.print(g);
  Serial.print(" ");
  delay(100);
}
void blue(){
   // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
 // Reading the output frequency
  b= pulseIn(sensorOut, LOW);  
 // Printing the BLUE (B) value 
  Serial.print("B=");
  Serial.print(b);
  Serial.print(" ");
  delay(100);
}
void li(int ang)
{int m,n,a;
  if (ang>pangl)
  {for(m=pangl;m<ang;m=m+5)
  {delay(20);
  tolift.write(m);
  }}
  else
  {for(m=pangl;m>ang;m=m-1)
  {delay(20);
  tolift.write(m);
  }} 
pangl=ang;
l=pangl;}
void hi(int ang)
{int m,n,a;
  if (ang>pangh)
  {for(m=pangh;m<ang;m=m+6)
  {
    delay(20);
  forward.write(m);
  }}
  else
  {for(m=pangh;m>ang;m=m-6)
  {
    delay(20);
  forward.write(m);
  }} 
pangh=ang;
h=pangh;}  
void bs (int ang)
{int m,n,a;
  if (ang>pangb)
  {for(m=pangb;m<ang;m=m+3)
  {
delay(20);
    base.write(m);
  }}
  else
  {for(m=pangb;m>ang;m=m-3)
  {
delay(20);
  base.write(m);
  }} 
pangb=ang;
bb=ang;
}
